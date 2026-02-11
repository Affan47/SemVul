estimate_rel_size(Relation rel, int32 *attr_widths,
				  BlockNumber *pages, double *tuples, double *allvisfrac)
{
	BlockNumber curpages;
	BlockNumber relpages;
	double		reltuples;
	BlockNumber relallvisible;
	double		density;

	switch (rel->rd_rel->relkind)
	{
		case RELKIND_RELATION:
		case RELKIND_INDEX:
		case RELKIND_MATVIEW:
		case RELKIND_TOASTVALUE:

			curpages = RelationGetNumberOfBlocks(rel);


			if (curpages < 10 &&
				rel->rd_rel->relpages == 0 &&
				!rel->rd_rel->relhassubclass &&
				rel->rd_rel->relkind != RELKIND_INDEX)
				curpages = 10;


			*pages = curpages;

			if (curpages == 0)
			{
				*tuples = 0;
				*allvisfrac = 0;
				break;
			}

			relpages = (BlockNumber) rel->rd_rel->relpages;
			reltuples = (double) rel->rd_rel->reltuples;
			relallvisible = (BlockNumber) rel->rd_rel->relallvisible;


			if (rel->rd_rel->relkind == RELKIND_INDEX &&
				relpages > 0)
			{
				curpages--;
				relpages--;
			}


			if (relpages > 0)
				density = reltuples / (double) relpages;
			else
			{


				int32		tuple_width;

				tuple_width = get_rel_data_width(rel, attr_widths);
				tuple_width += MAXALIGN(SizeofHeapTupleHeader);
				tuple_width += sizeof(ItemIdData);

				density = (BLCKSZ - SizeOfPageHeaderData) / tuple_width;
			}
			*tuples = rint(density * (double) curpages);


			if (relallvisible == 0 || curpages <= 0)
				*allvisfrac = 0;
			else if ((double) relallvisible >= curpages)
				*allvisfrac = 1;
			else
				*allvisfrac = (double) relallvisible / curpages;
			break;
		case RELKIND_SEQUENCE:

			*pages = 1;
			*tuples = 1;
			*allvisfrac = 0;
			break;
		case RELKIND_FOREIGN_TABLE:

			*pages = rel->rd_rel->relpages;
			*tuples = rel->rd_rel->reltuples;
			*allvisfrac = 0;
			break;
		default:

			*pages = 0;
			*tuples = 0;
			*allvisfrac = 0;
			break;
	}
}
