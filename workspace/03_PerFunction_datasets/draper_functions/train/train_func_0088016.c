dig__fwrite_port_D(double *buf,
		       int cnt, GVFILE * fp)
{
    int i, j;
    unsigned char *c1, *c2;

    if (Cur_Head->dbl_quick) {
	if (dig_fwrite(buf, PORT_DOUBLE, cnt, fp) == cnt)
	    return 1;
    }
    else {
	buf_alloc(cnt * PORT_DOUBLE);
	c1 = (unsigned char *)buf;
	c2 = (unsigned char *)buffer;
	for (i = 0; i < cnt; i++) {
	    for (j = 0; j < PORT_DOUBLE; j++)
		c2[j] = c1[Cur_Head->dbl_cnvrt[j]];
	    c1 += sizeof(double);
	    c2 += PORT_DOUBLE;
	}
	if (dig_fwrite(buffer, PORT_DOUBLE, cnt, fp) == cnt)
	    return 1;
    }
    return 0;
}
