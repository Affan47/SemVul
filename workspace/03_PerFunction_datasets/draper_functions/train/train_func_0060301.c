testface(int i, int j, int k, CUBE *old,
						   int face, int c1, int c2, int c3, int c4, PROCESS *p)
{
	CUBE new1;
    CUBES *oldcubes = p->cubes;


    int n, pos = old->corners[c1]->value > 0.0 ? 1 : 0;


    if ((old->corners[c2]->value > 0) == pos &&
	(old->corners[c3]->value > 0) == pos &&
	(old->corners[c4]->value > 0) == pos) return;

	float size = p->size;
	if(i*size + p->start.x > p->boundsX1
		|| i*size + p->start.x < p->boundsX2
		|| j*size + p->start.y > p->boundsY1
		|| j*size + p->start.y < p->boundsY2
		|| k*size + p->start.z > p->boundsZ1
		|| k*size + p->start.z < p->boundsZ2)
		return;
    if (setcenter(p->centers, i, j, k)) return;


    new1.i = i;
    new1.j = j;
    new1.k = k;


    for (n = 0; n < 8; n++)

	    new1.corners[n] = setcorner1(p, i+BIT(n,2), j+BIT(n,1), k+BIT(n,0));


    p->cubes = (CUBES *) mycalloc(1, sizeof(CUBES));
    p->cubes->cube = new1;
    p->cubes->next = oldcubes;
}
