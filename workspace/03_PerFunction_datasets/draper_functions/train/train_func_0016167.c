compute_maxrows(void)
{
    int n;
    filestruct *foo = openfile->edittop;

    if (!ISSET(SOFTWRAP)) {
	maxrows = editwinrows;
	return;
    }

    maxrows = 0;
    for (n = 0; n < editwinrows && foo; n++) {
	maxrows ++;
	n += strlenpt(foo->data) / COLS;
	foo = foo->next;
    }

    if (n < editwinrows)
	maxrows += editwinrows - n;

#ifdef DEBUG
    fprintf(stderr, "compute_maxrows(): maxrows = %ld\n", maxrows);
#endif
}
