doTextUndoOrRedo(DocIterator & cur, UndoElementStack & stack, UndoElementStack & otherstack)
{

	UndoElement & undo = stack.top();
	LYXERR(Debug::UNDO, "Undo element of group " << undo.group_id);


	DocIterator cell_dit = undo.cell.asDocIterator(&buffer_);

	doRecordUndo(ATOMIC_UNDO, cell_dit,
		undo.from, cell_dit.lastpit() - undo.end, undo.cur_after,
		undo.isFullBuffer, otherstack);
	otherstack.top().cur_after = undo.cur_before;


	DocIterator dit = undo.cell.asDocIterator(&buffer_);
	if (undo.isFullBuffer) {
		LASSERT(undo.pars, );

		delete otherstack.top().bparams;
		otherstack.top().bparams = new BufferParams(buffer_.params());
		buffer_.params() = *undo.bparams;
		swap(buffer_.paragraphs(), *undo.pars);
		delete undo.pars;
		undo.pars = 0;
	} else if (dit.inMathed()) {


		LASSERT(undo.array, );
		dit.cell().swap(*undo.array);
		delete undo.array;
		undo.array = 0;
	} else {

		Text * text = dit.text();
		LASSERT(text, );
		LASSERT(undo.pars, );
		ParagraphList & plist = text->paragraphs();


		ParagraphList::iterator first = plist.begin();
		advance(first, undo.from);
		ParagraphList::iterator last = plist.begin();
		advance(last, plist.size() - undo.end);
		plist.erase(first, last);


		first = plist.begin();
		advance(first, undo.from);


		ParagraphList::iterator pit = undo.pars->begin();
		ParagraphList::iterator const end = undo.pars->end();
		for (; pit != end; ++pit)
			pit->setInsetOwner(dit.realInset());
		plist.insert(first, undo.pars->begin(), undo.pars->end());
		delete undo.pars;
		undo.pars = 0;
	}
	LASSERT(undo.pars == 0, );
	LASSERT(undo.array == 0, );

	if (undo.cur_before.size())
		cur = undo.cur_before.asDocIterator(&buffer_);
	if (undo.lyx_clean)
		buffer_.markClean();
	else
		buffer_.markDirty();

	stack.pop();
}
