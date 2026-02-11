AddOne(tVertex p)
{
    tFace f;
    tEdge e, temp;
    long int vol;
    bool vis = BFALSE;


    f = faces;
    do {
	vol = VolumeSign(f, p);

	if (vol < 0) {
	    f->visible = VISIBLE;
	    vis = BTRUE;
	}
	f = f->next;
    } while (f != faces);


    if (!vis) {
	p->onhull = !ONHULL;
	return BFALSE;
    }


    e = edges;
    do {
	temp = e->next;
	if (e->adjface[0]->visible && e->adjface[1]->visible)

	    e->delete = REMOVED;
	else if (e->adjface[0]->visible || e->adjface[1]->visible)

	    e->newface = MakeConeFace(e, p);
	e = temp;
    } while (e != edges);
    return BTRUE;
}
