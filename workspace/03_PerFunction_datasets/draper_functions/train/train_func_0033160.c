dss_openssh_createkey(unsigned char **blob, int *len)
{
    char **b = (char **) blob;
    struct dss_key *dss;

    dss = snew(struct dss_key);
    if (!dss)
	return NULL;

    dss->p = getmp(b, len);
    dss->q = getmp(b, len);
    dss->g = getmp(b, len);
    dss->y = getmp(b, len);
    dss->x = getmp(b, len);

    if (!dss->p || !dss->q || !dss->g || !dss->y || !dss->x) {
	sfree(dss->p);
	sfree(dss->q);
	sfree(dss->g);
	sfree(dss->y);
	sfree(dss->x);
	sfree(dss);
	return NULL;
    }

    return dss;
}
