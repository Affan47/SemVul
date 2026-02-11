iscsi_add_text(struct iscsi_hdr *pdu, char *data, int max_data_length,
		char *param, char *value)
{
	int param_len = strlen(param);
	int value_len = strlen(value);
	int length = param_len + 1 + value_len + 1;


	int pdu_length = ntoh24(pdu->dlength);
	char *text = data;
	char *end = data + max_data_length;


	text += pdu_length;
	pdu_length += length;

	if (text + length >= end) {
		log_warning("Failed to add login text "
			    "'%s=%s'", param, value);
		return 0;
	}


	strncpy(text, param, param_len);
	text += param_len;


	*text++ = ISCSI_TEXT_SEPARATOR;


	strncpy(text, value, value_len);
	text += value_len;


	*text++ = '\0';


	hton24(pdu->dlength, pdu_length);

	return 1;
}
