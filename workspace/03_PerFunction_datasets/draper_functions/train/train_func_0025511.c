aim_mpmsg_addraw(aim_session_t *sess, aim_mpmsg_t *mpm,
	fu16_t charset, fu16_t charsubset, const fu8_t *data, fu16_t datalen)
{
	fu8_t *dup;

	if (!(dup = malloc(datalen)))
		return -1;
	memcpy(dup, data, datalen);

	if (mpmsg_addsection(sess, mpm, charset, charsubset, dup,
			datalen) == -1) {
		free(dup);
		return -1;
	}

	return 0;
}
