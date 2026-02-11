writeRange(const char *name, struct FPRange *range)

{
    char xname[GNAME_MAX], xmapset[GMAPSET_MAX];
    char buf[GNAME_MAX + sizeof(G3D_DIRECTORY) + 2],
	buf2[GMAPSET_MAX + sizeof(G3D_RANGE_ELEMENT) + 2];
    char xdr_buf[100];
    int fd;
    XDR xdr_str;

    if (G__name_is_fully_qualified(name, xname, xmapset)) {
	sprintf(buf, "%s/%s", G3D_DIRECTORY, xname);
	sprintf(buf2, "%s@%s", G3D_RANGE_ELEMENT, xmapset);
    }
    else {
	sprintf(buf, "%s/%s", G3D_DIRECTORY, name);
	sprintf(buf2, "%s", G3D_RANGE_ELEMENT);
    }

    fd = G_open_new(buf, buf2);
    if (fd < 0)
	goto error;

    if (range->first_time) {

	close(fd);
	return 0;
    }

    xdrmem_create(&xdr_str, xdr_buf, (u_int) G3D_XDR_DOUBLE_LENGTH * 2,
		  XDR_ENCODE);

    if (!xdr_double(&xdr_str, &(range->min)))
	goto error;
    if (!xdr_double(&xdr_str, &(range->max)))
	goto error;

    write(fd, xdr_buf, G3D_XDR_DOUBLE_LENGTH * 2);
    close(fd);
    return 0;

  error:
    G_remove(buf, buf2);
    sprintf(buf, "can't write range file for [%s in %s]", name, G_mapset());
    G_warning(buf);
    return -1;
}
