_bt_buildadd(BTWriteState *wstate, BTPageState *state, IndexTuple itup)
{
	Page		npage;
	BlockNumber nblkno;
	OffsetNumber last_off;
	Size		pgspc;
	Size		itupsz;


	CHECK_FOR_INTERRUPTS();

	npage = state->btps_page;
	nblkno = state->btps_blkno;
	last_off = state->btps_lastoff;

	pgspc = PageGetFreeSpace(npage);
	itupsz = IndexTupleDSize(*itup);
	itupsz = MAXALIGN(itupsz);


	if (itupsz > BTMaxItemSize(npage))
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
			errmsg("index row size %lu exceeds maximum %lu for index \"%s\"",
				   (unsigned long) itupsz,
				   (unsigned long) BTMaxItemSize(npage),
				   RelationGetRelationName(wstate->index)),
		errhint("Values larger than 1/3 of a buffer page cannot be indexed.\n"
				"Consider a function index of an MD5 hash of the value, "
				"or use full text indexing.")));


	if (pgspc < itupsz || (pgspc < state->btps_full && last_off > P_FIRSTKEY))
	{


		Page		opage = npage;
		BlockNumber oblkno = nblkno;
		ItemId		ii;
		ItemId		hii;
		IndexTuple	oitup;


		npage = _bt_blnewpage(state->btps_level);


		nblkno = wstate->btws_pages_alloced++;


		Assert(last_off > P_FIRSTKEY);
		ii = PageGetItemId(opage, last_off);
		oitup = (IndexTuple) PageGetItem(opage, ii);
		_bt_sortaddtup(npage, ItemIdGetLength(ii), oitup, P_FIRSTKEY);


		hii = PageGetItemId(opage, P_HIKEY);
		*hii = *ii;
		ItemIdSetUnused(ii);
		((PageHeader) opage)->pd_lower -= sizeof(ItemIdData);


		if (state->btps_next == NULL)
			state->btps_next = _bt_pagestate(wstate, state->btps_level + 1);

		Assert(state->btps_minkey != NULL);
		ItemPointerSet(&(state->btps_minkey->t_tid), oblkno, P_HIKEY);
		_bt_buildadd(wstate, state->btps_next, state->btps_minkey);
		pfree(state->btps_minkey);


		state->btps_minkey = CopyIndexTuple(oitup);


		{
			BTPageOpaque oopaque = (BTPageOpaque) PageGetSpecialPointer(opage);
			BTPageOpaque nopaque = (BTPageOpaque) PageGetSpecialPointer(npage);

			oopaque->btpo_next = nblkno;
			nopaque->btpo_prev = oblkno;
			nopaque->btpo_next = P_NONE;
		}


		_bt_blwritepage(wstate, opage, oblkno);


		last_off = P_FIRSTKEY;
	}


	if (last_off == P_HIKEY)
	{
		Assert(state->btps_minkey == NULL);
		state->btps_minkey = CopyIndexTuple(itup);
	}


	last_off = OffsetNumberNext(last_off);
	_bt_sortaddtup(npage, itupsz, itup, last_off);

	state->btps_page = npage;
	state->btps_blkno = nblkno;
	state->btps_lastoff = last_off;
}
