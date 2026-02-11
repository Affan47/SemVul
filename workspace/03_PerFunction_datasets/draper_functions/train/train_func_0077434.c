preorder_skip_subthread(ARTICLE *art)
{
    while (!A_SIBLING(art))
	if (!(art = A_PARENT(art)))
	    return NULL;

    return A_SIBLING(art);
}
