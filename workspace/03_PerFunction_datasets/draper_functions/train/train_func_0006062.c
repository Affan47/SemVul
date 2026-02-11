add_reply(VALUE_PAIR** vp,
		      const char* name, const uint8_t *value, size_t len)
{
	VALUE_PAIR *reply_attr;
	reply_attr = pairmake(name, "", T_OP_EQ);
	if (!reply_attr) {
		DEBUG("rlm_eap_sim: "
		      "add_reply failed to create attribute %s: %s\n",
		      name, fr_strerror());
		return;
	}

	memcpy(reply_attr->vp_strvalue, value, len);
	reply_attr->length = len;
	pairadd(vp, reply_attr);
}
