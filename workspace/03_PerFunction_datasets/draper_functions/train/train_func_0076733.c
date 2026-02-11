pvr2_std_id_to_str(char *bufPtr, unsigned int bufSize,
				v4l2_std_id id)
{
	unsigned int idx1,idx2;
	const struct std_name *ip,*gp;
	int gfl,cfl;
	unsigned int c1,c2;
	cfl = 0;
	c1 = 0;
	for (idx1 = 0; idx1 < ARRAY_SIZE(std_groups); idx1++) {
		gp = std_groups + idx1;
		gfl = 0;
		for (idx2 = 0; idx2 < ARRAY_SIZE(std_items); idx2++) {
			ip = std_items + idx2;
			if (!(gp->id & ip->id & id)) continue;
			if (!gfl) {
				if (cfl) {
					c2 = scnprintf(bufPtr,bufSize,";");
					c1 += c2;
					bufSize -= c2;
					bufPtr += c2;
				}
				cfl = !0;
				c2 = scnprintf(bufPtr,bufSize,
					       "%s-",gp->name);
				gfl = !0;
			} else {
				c2 = scnprintf(bufPtr,bufSize,"/");
			}
			c1 += c2;
			bufSize -= c2;
			bufPtr += c2;
			c2 = scnprintf(bufPtr,bufSize,
				       ip->name);
			c1 += c2;
			bufSize -= c2;
			bufPtr += c2;
		}
	}
	return c1;
}
