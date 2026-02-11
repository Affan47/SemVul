find_neighbors(EW * ewptr, NEIGHBOR * nbr_head, SHORT row, SHORT col,
	       int npoints, SHORT * neighbors)
{
    MELEMENT **Mptr;
    int westward = 1;
    double distance;

    Mptr = &ewptr->west;
    do {
	if (*Mptr) {
	    distance = triangulate(*Mptr, row, col);

	    if (*neighbors < npoints)
		add_neighbor(Mptr, nbr_head, distance, ++(*neighbors));
	    else if (!replace_neighbor(Mptr, nbr_head, distance))
		*Mptr = NULL;

	    if (*Mptr) {
		if (westward)
		    *Mptr = (*Mptr)->prior;
		else
		    *Mptr = (*Mptr)->next;
	    }
	}

	Mptr = &ewptr->east;
    } while (westward--);
    return 0;
}
