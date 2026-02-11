set_curr_art(ARTICLE *art, int center)
{
    if (global.mode == NewsModeThread) {
	if (global.curr_art && global.curr_art != art)
	    ArtTreeNodeSetSelected(main_widgets.arttree,
				   (ART_TREE_NODE *)global.curr_art, False);

	if (art) {
	    ArtTreeNodeSetSelected(main_widgets.arttree,
				   (ART_TREE_NODE *)art, True);
	    if (center)
		ArtTreeNodeMakeVisible(main_widgets.arttree,
				       (ART_TREE_NODE*)art);
	}
    }

    global.curr_art = art;
    if (art)
	set_curr_subj(art->subject);
}
