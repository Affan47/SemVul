G_rle_encode(char *src, char *dst, int nofElts, int eltLength)
{
    int length, nofEqual;
    char *head, *tail, *headStop, *headStop2;

    if (nofElts <= 0)
	G3d_fatalError("trying to encode 0-length list");

    length = 0;
    nofEqual = 1;
    head = src + eltLength;
    tail = src;

    headStop = src + nofElts * eltLength;

    while (head != headStop) {
	headStop2 = head + eltLength;

	while (head != headStop2) {
	    if (*head != *tail) {
		dst = rle_length2code(nofEqual, dst);
		tail = headStop2 - eltLength * (nofEqual + 1);
		head = tail + eltLength;

		while (tail != head)
		    *dst++ = *tail++;
		length += G_rle_codeLength(nofEqual) + eltLength;
		nofEqual = 1;
		tail = headStop2 - eltLength;
		break;
	    }
	    head++;
	    tail++;
	}

	if (head == headStop2) {
	    nofEqual++;
	    continue;
	}

	head = headStop2;
    }

    dst = rle_length2code(nofEqual, dst);
    tail = headStop - eltLength * nofEqual;
    head = tail + eltLength;
    while (tail != head)
	*dst++ = *tail++;
    length += G_rle_codeLength(nofEqual) + eltLength;
    dst = rle_length2code(-1, dst);
    length += G_rle_codeLength(-1);
    rle_code2length(dst - 2, &nofEqual);
}
