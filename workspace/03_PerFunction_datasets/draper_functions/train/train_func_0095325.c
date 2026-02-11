link_child(ARTICLE *child)
{
    ARTICLE	*art = A_PARENT(child);

    if (art) {
	art = A_CHILD1(art);
	if (!art || child->date < art->date) {
	    SIBLING(child) = (ART_TREE_NODE *)art;
	    CHILD1(A_PARENT(child)) = (ART_TREE_NODE *)child;
	} else {
	    while (A_SIBLING(art) && A_SIBLING(art)->date <= child->date)
		art = A_SIBLING(art);
	    SIBLING(child) = SIBLING(art);
	    SIBLING(art) = (ART_TREE_NODE *)child;
	}
    } else {
	SUBJECT	*subj = child->subject;

	art = subj->thread;
	if (!art || child->date < art->date) {
	    do {
		subj->thread = child;
		subj = subj->prev;
	    } while (subj && subj->thread == art);

	    subj = child->subject->next;

	    while (subj && subj->thread == art) {
		subj->thread = child;
		subj = subj->next;
	    }
	    SIBLING(child) = (ART_TREE_NODE *)art;
	} else {
	    while (A_SIBLING(art) && A_SIBLING(art)->date <= child->date)
		art = A_SIBLING(art);
	    SIBLING(child) = SIBLING(art);
	    SIBLING(art) = (ART_TREE_NODE *)child;
	}
    }
}
