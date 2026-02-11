CDB___os_openhandle(name, flags, mode, fhp)
	const char *name;
	int flags, mode;
	DB_FH *fhp;
{
	int ret, try;

	memset(fhp, 0, sizeof(*fhp));

	for (ret = 0, try = 1; try < 4; ++try) {


#ifdef _MSC_VER

        mode |= _O_BINARY;
#endif

		fhp->fd = CDB___db_jump.j_open != NULL ?
		    CDB___db_jump.j_open(name, flags, mode) :
#ifdef __VMS
		    open(name, flags, mode, "shr=get,put,upd,del,upi");
#else
		    open(name, flags, mode);
#endif


		if (fhp->fd == -1) {


			ret = CDB___os_get_errno();
			if (ret == ENFILE || ret == EMFILE || ret == ENOSPC) {
				(void)CDB___os_sleep(try * 2, 0);
				continue;
			}
		} else
			F_SET(fhp, DB_FH_VALID);
		break;
	}
	return (ret);
}
