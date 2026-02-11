cli_msexpand(cli_ctx *ctx, int ofd)
{
	const struct msexp_hdr *hdr;
	uint8_t i, mask, bits;
	unsigned char buff[B_SIZE], wbuff[RW_SIZE];
	const unsigned char *rbuff;
	unsigned int j = B_SIZE - 16, k, l, r = 0, w = 0, rbytes = 0, wbytes = 0;
	fmap_t *map = *ctx->fmap;
	off_t cur_off = sizeof(*hdr);
	unsigned int fsize;
	int ret;

    if(!(hdr = fmap_need_off_once(map, 0, sizeof(*hdr))))
	return CL_EREAD;

    if(EC32(hdr->magic1) != MAGIC1 || EC32(hdr->magic2) != MAGIC2 || EC16(hdr->magic3) != MAGIC3) {
	cli_dbgmsg("MSEXPAND: Not supported file format\n");
	return CL_EFORMAT;
    }

    fsize = EC32(hdr->fsize);
    cli_dbgmsg("MSEXPAND: File size from header: %u\n", fsize);

    if(cli_checklimits("MSEXPAND", ctx, fsize, 0, 0)!=CL_CLEAN)
        return CL_SUCCESS;

    memset(buff, 0, B_SIZE);
    while(1) {

	if(!rbytes || (r == rbytes)) {
	    READBYTES;
	}

	bits = rbuff[r]; r++;

	mask = 1;
	for(i = 0; i < 8; i++) {
	    if(bits & mask) {
		if(r == rbytes) {
		    READBYTES;
		}

		if(w == RW_SIZE) {
		    WRITEBYTES;
		}

		wbuff[w] = buff[j] = rbuff[r];
		r++; w++;
		j++; j %= B_SIZE;
	    } else {
		if(r == rbytes) {
		    READBYTES;
		}
		k = rbuff[r]; r++;

		if(r == rbytes) {
		    READBYTES;
		}
		l = rbuff[r]; r++;

		k += (l & 0xf0) << 4;
		l = (l & 0x0f) + 3;
		while(l--) {
		    if(w == RW_SIZE) {
			WRITEBYTES;
		    }
		    wbuff[w] = buff[j] = buff[k];
		    w++;
		    k++; k %= B_SIZE;
		    j++; j %= B_SIZE;
		}
	    }
	    mask *= 2;
	}
    }

    if(w) {
	WRITEBYTES;
    }

    return CL_SUCCESS;
}
