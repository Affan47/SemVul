has_bip_P()


{

    int i,j,w,z;
    EDGE *e,*e1,*ez,*ezlast;

    for (i = 0; i < nv; ++i)
    if (degree[i] == 4)
    {
	e = firstedge[i];
	j = 0;
	if (degree[e->end] == 4) {e1 = e; ++j;} e=e->next;
	if (degree[e->end] == 4) {e1 = e; ++j;} e=e->next;
	if (degree[e->end] == 4) {e1 = e; ++j;} e=e->next;
	if (degree[e->end] == 4) {e1 = e; ++j;}
	if (j != 1) continue;

	e = e1->next->next;

	w = e->end;
	z = e1->invers->next->next->end;

	if (degree[z] != 4)
	{
            ezlast = ez = firstedge[z];
            do
            {
                if (ez->end == w) break;
                ez = ez->next;
            } while (ez != ezlast);
            if (ez->end == w) continue;
	}

	return e;
    }
    return NULL;
}
