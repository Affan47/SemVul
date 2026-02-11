compute_area(_set *A, _set* B)
{
    if (B->next == NULL)
	return B->p->x*A->p->y - A->p->x*B->p->y;
    else
	return B->p->x*B->next->p->y - B->next->p->x*B->p->y
	       + compute_area(A, B->next);
}
