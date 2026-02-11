blk_cmp(BLOCK *a, BLOCK *b)
{


	if (a == b) {

		return FALSE;
	}
	if (a == NULL || b == NULL) {

		return TRUE;
	}


	if (a->datalen != b->datalen) {

		return TRUE;
	}


	if (memcmp(a->data, b->data, a->datalen) != 0) {

		return TRUE;
	}


	return FALSE;
}
