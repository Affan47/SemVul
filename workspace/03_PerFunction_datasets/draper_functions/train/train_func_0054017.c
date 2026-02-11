rescode_get_data(const struct l2tp_attr_t *result_attr,
			    uint16_t *res, uint16_t *err, char **err_msg)
{
	struct l2tp_avp_result_code *resavp = NULL;
	int msglen;

	if (result_attr->length != 2 && result_attr->length < sizeof(*resavp))
		return -1;

	if (result_attr->length == 2) {

		*res = ntohs(*(const uint16_t *)result_attr->val.octets);
		return 1;
	}

	resavp = (struct l2tp_avp_result_code *)result_attr->val.octets;
	*res = ntohs(resavp->result_code);
	*err = ntohs(resavp->error_code);
	msglen = result_attr->length - sizeof(*resavp);
	if (msglen <= 0)
		return 2;

	*err_msg = _malloc(msglen + 1);
	if (err_msg) {
		memcpy(*err_msg, resavp->error_msg, msglen);
		(*err_msg)[msglen] = '\0';
	}

	return 3;
}
