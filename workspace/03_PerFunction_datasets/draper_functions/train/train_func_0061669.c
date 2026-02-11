doRecordUndo(UndoKind kind,
	DocIterator const & cell,
	pit_type first_pit, pit_type last_pit,
	StableDocIterator const & cur_before,
	bool isFullBuffer,
	UndoElementStack & stack)
{
	if (!group_level) {
		LYXERR0("There is no group open (creating one)");
		++group_id;
	}

	if (first_pit > last_pit)
		swap(first_pit, last_pit);


	pit_type from = first_pit;
	pit_type end = cell.lastpit() - last_pit;
	if (!undo_finished_
	    && kind != ATOMIC_UNDO
	    && !stack.empty()
	    && samePar(stack.top().cell, cell)
	    && stack.top().kind == kind
	    && stack.top().from == from
	    && stack.top().end == end) {

		stack.top().cur_after = StableDocIterator();
		return;
	}

	if (isFullBuffer)
		LYXERR(Debug::UNDO, "Create full buffer undo element of group " << group_id);
	else
		LYXERR(Debug::UNDO, "Create undo element of group " << group_id);

	UndoElement undo(kind, cur_before, cell, from, end, 0, 0,
	                 buffer_.params(), isFullBuffer, buffer_.isClean(), group_id);


	if (cell.inMathed()) {

		MathData & ar = cell.cell();
		undo.array = new MathData(ar.buffer(), ar.begin(), ar.end());
	} else {


		Text const * text = cell.text();
		LASSERT(text, );
		ParagraphList const & plist = text->paragraphs();
		ParagraphList::const_iterator first = plist.begin();
		advance(first, first_pit);
		ParagraphList::const_iterator last = plist.begin();
		advance(last, last_pit + 1);
		undo.pars = new ParagraphList(first, last);
	}


	stack.push(undo);

}
