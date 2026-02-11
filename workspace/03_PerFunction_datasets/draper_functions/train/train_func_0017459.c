decode_transfer_encoding(char *line)
{
	char *ep;

	switch (transfer_encoding) {
	case TE_QP:
		ep = line + strlen(line);
		decode_q_segment(line, line, ep, 0);
		break;
	case TE_BASE64:
		ep = line + strlen(line);
		decode_b_segment(line, line, ep);
		break;
	case TE_DONTCARE:
		break;
	}
}
