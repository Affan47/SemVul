System_uname(CTX ctx, ksfp_t *sfp _RIX)
{
	kMap *mdata = KNH_TNULL(Map);
	struct utsname buf;
	int ret = uname(&buf);
	if (ret == -1) {
		KNH_NTRACE2(ctx, "uname", K_PERROR, KNH_LDATA0);
	} else {
		mdata = new_DataMap(ctx);
		knh_DataMap_setString(ctx, mdata, "sysname", buf.sysname);
		knh_DataMap_setString(ctx, mdata, "nodename", buf.nodename);
		knh_DataMap_setString(ctx, mdata, "release", buf.release);
		knh_DataMap_setString(ctx, mdata, "version", buf.version);
		knh_DataMap_setString(ctx, mdata, "machine", buf.machine);
		KNH_NTRACE2(ctx, "uname", K_OK, KNH_LDATA0);

	}
	RETURN_(mdata);
}
