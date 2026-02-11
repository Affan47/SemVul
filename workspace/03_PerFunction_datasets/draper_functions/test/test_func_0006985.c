action_tag_thread(Widget w, XEvent *event,
		       String *params, Cardinal *no_params)
{
    ARTICLE	*art;
    SUBJECT	*subj;
    int		only_unread = True;
    char	message[80];

    if (global.busy || (global.mode != NewsModeGroup &&
			global.mode != NewsModeThread))
	return;

    if (!global.curr_subj) {
	set_message("No selected subject!", True);
	return;
    }

    if (*no_params > 0)
	only_unread = False;

    for (art = global.curr_subj->thread ; art ;
	 art = next_in_thread_preorder(art)) {
	if (art->from && !(only_unread && art->read) && !is_tagged(art)) {
	    add_tag(art);
	    if (global.mode == NewsModeThread)
		ArtTreeNodeSetOuter(main_widgets.arttree,
				    (ART_TREE_NODE *)art, True);
	}
    }

    subj = global.curr_subj;
    art = subj->thread;
    while (subj->prev && subj->prev->thread == art)
	subj = subj->prev;

    while (subj && subj->thread == art) {
	update_subj_entry(subj);
	subj = subj->next;
    }

    sprintf(message, "%ld tagged articles", no_tagged);
    set_message(message, False);
}
