_dxffile_open(char *name, int rw)
{
	int i, fd=-1;

	if (!name) {
		DXSetError(ERROR_BAD_PARAMETER, "no filename");
		return ERROR;
	}

#if DXD_HAS_LIBIOP
	{
		int rc;

		if (pfsname(name)) {
			pfs_stat_t ps;

			rc = pfs_stat(name, &ps);
			if (rc < 0) {

				if (rw == 0) {
					DXSetError(ERROR_DATA_INVALID, "can't open file '%s'", name);
					return ERROR;
				}

				rc = pfs_create(name, 0);
				if (rc < 0) {
					DXSetError(ERROR_DATA_INVALID, pfs_errmsg(rc));
					return ERROR;
				}
			}

			return OK;
		}
	}
#endif

	switch(rw) {
	case 0:
		fd = open(name, O_RDONLY);
		if (fd < 0) {
			DXSetError(ERROR_DATA_INVALID, "can't open file '%s'", name);
			return ERROR;
		}
		break;
	case 1:
	case 2:
		fd = open(name, O_RDWR);
		if (fd < 0) {
			fd = open(name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			if (fd < 0) {
				DXSetError(ERROR_DATA_INVALID,
				"can't open/create file '%s'", name);
				return ERROR;
			}
		}
		break;
	}


	for (i=0; i<NSLOTS; i++)
		if (of[i].fd == -1)
			break;

	if (i == NSLOTS) {
		DXSetError(ERROR_DATA_INVALID, "too many datasets open");
		return ERROR;
	}

	of[i].fd = fd;
	of[i].socket = 0;
	of[i].sndbytes = of[i].rcvbytes = 0;
	strcpy(of[i].fname, name);
	return OK;

}
