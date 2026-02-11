gar_get_object_lbl(struct gobject *o)
{
	char buf[8192];
	off_t off;
	int type,rc;
	struct gar_subfile *gs = NULL;
	struct gpoint *gp;
	struct gpoly *gpl;
	struct gar_road *rd;

	type = L_LBL;
	switch (o->type) {
	case GO_POINT:
		gp = o->gptr;
		if (gp->is_poi)
			type = L_POI;
		gs = gp->subdiv->subfile;
		off = gp->lbloffset;
		if (gp->type == 0)
			return NULL;
		break;
	case GO_POLYLINE:
	case GO_POLYGON:
		gpl = o->gptr;
		if (gpl->netlbl)
			type = L_NET;
		gs = gpl->subdiv->subfile;
		off = gpl->lbloffset;
		break;
	case GO_ROAD: {
			int i,sz = 0;
			rd = o->gptr;
			for (i=0;i < 4; i++) {
				if (rd->labels[i]) {
					sz += gar_get_lbl(rd->sub, rd->labels[i], L_LBL,
					 (unsigned char *)buf+sz, sizeof(buf)-sz);
					strcat(buf, "/");
				}
			}
			if (sz)
				return strdup(buf);
			else
				return NULL;
		}
	default:
		log(1, "Error unknown object type:%d\n", o->type);
		return NULL;
	}
	rc = gar_get_lbl(gs, off, type, (unsigned char *)buf, sizeof(buf));
	if (rc > 0) {
		log(15, "LBL: type:%d [%d] offset=%03lX [%s]\n", o->type, type, off, buf);
		return strdup(buf);
	}
	return NULL;
}
