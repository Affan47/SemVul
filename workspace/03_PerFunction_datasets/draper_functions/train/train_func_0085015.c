applyAllGeneratingRules ( DlCompletionTree* node )
{
	const CGLabel& label = node->label();
	for ( CGLabel::const_iterator p = label.begin_cc(), p_end = label.end_cc(); p != p_end; ++p )
	{

		if ( isPositive(p->bp()) )
			continue;

		switch ( DLHeap[*p].Type() )
		{
		case dtForall:
		case dtLE:
			addExistingToDoEntry ( node, label.getCCOffset(p), "ubd" );
			break;

		default:
			break;
		}
	}
}
