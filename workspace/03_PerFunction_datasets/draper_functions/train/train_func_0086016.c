stun_attr_add_integrity_by_user_short_term_str(u08bits *buf, size_t *len, u08bits *uname, st_password_t pwd, SHATYPE shatype)
{
	if(stun_attr_add_str(buf, len, STUN_ATTRIBUTE_USERNAME, uname, strlen((s08bits*)uname))<0)
			return -1;

	hmackey_t key;
	return stun_attr_add_integrity_str(TURN_CREDENTIALS_SHORT_TERM, buf, len, key, pwd, shatype);
}
