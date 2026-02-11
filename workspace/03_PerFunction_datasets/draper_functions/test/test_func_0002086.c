write_netdump(int fd, void *bufptr, int cnt, ulong addr, physaddr_t paddr)
{
	off_t offset;
	struct pt_load_segment *pls;
	int i;

	offset = 0;

        switch (DUMPFILE_FORMAT(nd->flags))
	{
	case NETDUMP_ELF32:
		offset = (off_t)paddr + (off_t)nd->header_size;
		break;

	case NETDUMP_ELF64:
	case KDUMP_ELF32:
	case KDUMP_ELF64:
		if (nd->num_pt_load_segments == 1) {
			offset = (off_t)paddr + (off_t)nd->header_size;
			break;
		}

		for (i = offset = 0; i < nd->num_pt_load_segments; i++) {
			pls = &nd->pt_load_segments[i];
			if ((paddr >= pls->phys_start) &&
			    (paddr < pls->phys_end)) {
				offset = (off_t)(paddr - pls->phys_start) +
					pls->file_offset;
				break;
			}
		}

		if (!offset)
	                return READ_ERROR;

		break;
	}

        if (lseek(nd->ndfd, offset, SEEK_SET) == -1)
                return SEEK_ERROR;

        if (write(nd->ndfd, bufptr, cnt) != cnt)
                return READ_ERROR;

        return cnt;
}
