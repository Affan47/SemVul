newdbl (double x)
{
    NODE *n = new_node(NUM);

    if (n != NULL) {
	n->v.xval = x;
    }

    return n;
}
