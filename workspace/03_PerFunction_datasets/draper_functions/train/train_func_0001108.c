mfgets(char *s, int size, mFILE *mf) {
    int i;

    if (mf == m_channel[0]) init_mstdin();
    *s = 0;
    for (i = 0; i < size-1;) {
	if (mf->offset < mf->size) {
	    s[i] = mf->data[mf->offset++];
	    if (s[i++] == '\n')
		break;
	} else {
	    mf->eof = 1;
	    break;
	}
    }

    s[i] = 0;
    return i ? s : NULL;
}
