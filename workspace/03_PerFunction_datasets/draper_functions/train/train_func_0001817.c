knh_buff_addPackagePath(CTX ctx, kBytes *ba, size_t pos, kbytes_t pkgname)
{
	char *epath = knh_getenv("KONOHA_PACKAGE");
	if(epath != NULL && isFoundPackage(ctx, ba, pos, B(epath), pkgname)) {
		return 1;
	}
	kString *tpath = knh_getPropertyNULL(ctx, STEXT("konoha.package.path"));
	if(tpath != NULL && isFoundPackage(ctx, ba, pos, S_tobytes(tpath), pkgname)) {
		return 1;
	}
	tpath = knh_getPropertyNULL(ctx, STEXT("user.package.path"));
	if(tpath != NULL && isFoundPackage(ctx, ba, pos, S_tobytes(tpath), pkgname)) {
		return 1;
	}
	return 0;
}
