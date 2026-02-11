data_buf_input (int fd, buf_t *b, chn_t *ch)
{
int l;

    if (!b->cur)
	b->cur = new_sbuf();
    else if (b->cur->flen < SBIMIN) {


#ifdef DEBUG
	if (b->cur->next) {

	    tesc_emerg (CHN_MSG, MF_ERR, "data_buf_input(): buffer corrupt\n");
	    tesc_emerg (CHN_MSG, MF_EOF, "\n");
	    exit (1);
	}
#endif
	b->cur->next = new_sbuf();
	b->cur = b->cur->next;
    }


    if ((l = read (fd, b->cur->ffree, b->cur->flen)) == -1) {


	mlpx_printf (ch->id, MF_ERR, "read(): %s\n", strerror(errno));
	return -1;
    }

    if (l == 0) {

	return -2;
    }


    b->cur->ffree += l;
    b->cur->flen -= l;


    try_output (b, ch);

    return 0;
}
