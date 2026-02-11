DER_SetUInteger(PLArenaPool *arena, SECItem *it, PRUint32 ui)
{
    unsigned char bb[5];
    int len;

    bb[0] = 0;
    bb[1] = (unsigned char) (ui >> 24);
    bb[2] = (unsigned char) (ui >> 16);
    bb[3] = (unsigned char) (ui >> 8);
    bb[4] = (unsigned char) (ui);


    if (ui > 0x7f) {
	if (ui > 0x7fff) {
	    if (ui > 0x7fffffL) {
		if (ui >= 0x80000000L) {
		    len = 5;
		} else {
		    len = 4;
		}
	    } else {
		len = 3;
	    }
	} else {
	    len = 2;
	}
    } else {
	len = 1;
    }

    it->data = (unsigned char *)PORT_ArenaAlloc(arena, len);
    if (it->data == NULL) {
	return SECFailure;
    }

    it->len = len;
    PORT_Memcpy(it->data, bb + (sizeof(bb) - len), len);

    return SECSuccess;
}
