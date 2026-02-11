init_mstdin(void) {
    static int done_stdin = 0;
    if (done_stdin)
	return;

    m_channel[0]->data = mfload(stdin, NULL, &m_channel[0]->size, 1);
    m_channel[0]->mode = MF_READ;
    done_stdin = 1;
}
