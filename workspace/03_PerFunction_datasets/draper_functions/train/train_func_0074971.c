replace_neighbor(MELEMENT ** Mptr,
		     NEIGHBOR * nbr_head, double distance)
{
    NEIGHBOR *furthest;

    furthest = nbr_head->next;
    if (distance < furthest->distance) {

	if (!ll)
	    *(furthest->searchptr) = NULL;

	furthest->distance = distance;
	furthest->Mptr = *Mptr;
	furthest->searchptr = Mptr;


	if (furthest->next && (furthest->distance < furthest->next->distance))
	    sort_neighbors(nbr_head, distance);
	return (1);
    }
    else
	return (0);
}
