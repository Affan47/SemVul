zd1201_getconfig16(struct zd1201 *zd, int rid, short *val)
{
	int err;
	__le16 zdval;

	err = zd1201_getconfig(zd, rid, &zdval, sizeof(__le16));
	if (err)
		return err;
	*val = le16_to_cpu(zdval);
	return 0;
}
