SECITEM_ReallocItem(PLArenaPool *arena, SECItem *item, unsigned int oldlen,
		    unsigned int newlen)
{
    PORT_Assert(item != NULL);
    if (item == NULL) {

	return SECFailure;
    }


    if (oldlen == 0) {
	PORT_Assert(item->data == NULL || item->len == 0);
	if (newlen == 0) {

	    return SECSuccess;
	}
	item->len = newlen;
	if (arena != NULL) {
	    item->data = PORT_ArenaAlloc(arena, newlen);
	} else {
	    item->data = PORT_Alloc(newlen);
	}
    } else {
	if (arena != NULL) {
	    item->data = PORT_ArenaGrow(arena, item->data, oldlen, newlen);
	} else {
	    item->data = PORT_Realloc(item->data, newlen);
	}
    }

    if (item->data == NULL) {
	return SECFailure;
    }

    return SECSuccess;
}
