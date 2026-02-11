_ml_P_TTY_tcsetattr (ml_state_t *msp, ml_val_t arg)
{
    int              sts, fd = REC_SELINT(arg, 0);
    int              action = REC_SELINT(arg, 1);
    ml_val_t         termio_rep = REC_SEL(arg, 2);
    struct termios   data;

    data.c_iflag = REC_SELWORD(termio_rep, 0);
    data.c_oflag = REC_SELWORD(termio_rep, 1);
    data.c_cflag = REC_SELWORD(termio_rep, 2);
    data.c_lflag = REC_SELWORD(termio_rep, 3);

    memcpy (data.c_cc, GET_SEQ_DATAPTR(void, REC_SEL(termio_rep, 4)), NCCS);
    sts = cfsetispeed (&data, REC_SELWORD(termio_rep, 5));
    if (sts < 0)
	return RAISE_SYSERR(msp, sts);
    sts = cfsetospeed (&data, REC_SELWORD(termio_rep, 6));
    if (sts < 0)
	return RAISE_SYSERR(msp, sts);

    sts = tcsetattr(fd, action, &data);

    CHK_RETURN_UNIT(msp, sts)

}
