segment_get(SEGMENT * SEG, void *buf, int row, int col)
{
    int index, n, i;

    segment_address(SEG, row, col, &n, &index);
    if ((i = segment_pagein(SEG, n)) < 0)
	return -1;

    memcpy(buf, &SEG->scb[i].buf[index], SEG->len);

    return 1;
}
