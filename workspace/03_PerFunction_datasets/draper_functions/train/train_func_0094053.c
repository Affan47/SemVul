insert_or_match_mat(mat, mode)
Transform mat;
int mode;
{
	struct node *n = NULL, *p;
	float d;
	struct node tnode;
	double getnorm();

	if (debug == 4)	traverse_list(head);

	if (mode & INSERT ) n = alloc_node();
	else if (mode & MATCH)  n = &tnode;

	else n->type = 0;

	n->norm = getnorm(metric, mat);

	TmCopy(mat, n->t);

	if (head == NULL)
	    {
	    if (mode & MATCH)	return(0);
	    else if (mode & INSERT)	{
	        head = n;
	        return(1);
	    	}
	    }

	for (p = head; p != NULL; )	{
	    d = fabs(p->norm - n->norm);
	    if (ABS(d) < epsilon)	{
		if (mode & INSERT)	{

		    p->num++;
		    for (  ; p->same != NULL; p = p->same) ;

		    p->same = n;
		    n->p = p;
		    return(1);
		    }
		else {
		    for (  ; p != NULL; p = p->same)
			if (is_same(p->t, n->t))
				return( 1 );
		    return(0);
		    }
		}
	    else if (d > 0)	{
		if (p->r == NULL)	{
		    if (mode & INSERT)	{
			p->r = n;
			n->p = p;
			return(1);
			}
		    else 	{
			return(0);
		        }
		    }
		else	p = p->r;
		}
	    else if (d < 0)	{
		if (p->l == NULL)	{
		    if (mode & INSERT)    {
		        p->l = n;
		        n->p = p;
		        return(1);
		        }
		    else 	{
			return(0);
			}
		    }
		else	p = p->l;
		}
	    }
	return 0;
}
