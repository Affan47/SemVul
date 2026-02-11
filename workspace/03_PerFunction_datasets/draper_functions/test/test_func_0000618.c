index_fetchheader(struct index_state *state,
			      const char *msg_base,
			      unsigned long msg_size,
			      unsigned size,
			      struct strlist *headers,
			      struct strlist *headers_not)
{
    char *buf;


    if (!msg_base) {
	prot_printf(state->out, "\"\"");
	return;
    }

    buf = index_readheader(msg_base, msg_size, 0, size);

    index_pruneheader(buf, headers, headers_not);

    size = strlen(buf);
    prot_printf(state->out, "{%u}\r\n%s\r\n", size+2, buf);
}
