clear_tagged_articles(void)
{
    SUBJECT	*subj;
    ARTICLE	*thread;
    long	i;

    switch (global.mode) {
    case NewsModeThread:
	if (global.curr_subj)
	    thread = global.curr_subj->thread;
	else if (global.curr_art)
	    thread = global.curr_art->subject->thread;
	else
	    thread = NULL;

	for (i = 0 ; i < no_tagged ; i++)
	    if (tagged_articles[i]->subject->thread == thread)
		ArtTreeNodeSetOuter(main_widgets.arttree,
				    (ART_TREE_NODE *)tagged_articles[i],
				    False);


    case NewsModeGroup:
	for (subj = get_subjects(main_thr) ; subj ; subj = subj->next) {
	    if (subj->has_tagged) {
		subj->has_tagged = False;
		update_subj_entry(subj);
	    }
	}
	break;
    default:
	break;
    }

    XtFree((char *)tagged_articles);
    tagged_articles = NULL;
    no_tagged = 0;
    no_alloc = 0;
}
