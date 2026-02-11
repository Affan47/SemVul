s2b_insert_rec_in_coord(M_Coordinate2D *c, SWFShapeRec *srec)
{
	u32 i, j;
	srec->path->idx = gf_malloc(sizeof(u32)*srec->path->nbPts);

	for (i=0; i<srec->path->nbPts; i++) {
		for (j=0; j<c->point.count; j++) {
			if ( (c->point.vals[j].x == srec->path->pts[i].x) && (c->point.vals[j].y == srec->path->pts[i].y)) {
				break;
			}
		}
		if (j==c->point.count) {
			c->point.count++;
			c->point.vals = gf_realloc(c->point.vals, sizeof(SFVec2f)*c->point.count);
			c->point.vals[j] = srec->path->pts[i];
		}
		srec->path->idx[i] = j;
	}
}
