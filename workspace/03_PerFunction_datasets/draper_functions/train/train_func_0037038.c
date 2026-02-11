add_geodesic(Geod *g, char *str)
{
    int ok;
    float r;

    VVINIT(g->pts, P, 20);
    ok = sscanf(str, "%d,%f,%f,%f,%f,%f,%f,%f",
	&g->faceno, &g->base.x, &g->base.y, &g->base.z,
	&g->dir.x, &g->dir.y, &g->dir.z, &g->maxlength);

    if(ok < 7) {
	fprintf(stderr, "Geodesic must have form:  faceno,X0,Y0,Z0,X1,Y1,Z1\n\
where X0,Y0,Z0 define the base point, X1,Y1,Z1 the direction,\n\
and faceno is the integer index of the face on which the base-point lies.\n");
	exit(1);
    }


    VSUB(&g->dir, &g->base, &g->dir);
    r = VLENGTH(&g->dir);
    if(r)
	VSCALE(&g->dir, 1/r);
}
