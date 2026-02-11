remove_point(struct Point *p)
{
    struct Point *f = p->father;
    struct Point *l = p->left_brother;
    struct Point *r = p->right_brother;

    if (l != NULL)
	l->right_brother = r;
    if (r != NULL)
	r->left_brother = l;

    if (f->rightmost_son == p)
	f->rightmost_son = NULL;

    p->father = NULL;
    p->left_brother = NULL;
    p->right_brother = NULL;

}
