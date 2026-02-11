get_ssosos(DBusMessage *rep, int msgid)
{
	int ret;
	char *s1, *s2, *s3, *s4;
	ret = cm_tdbusm_get_ssosos(rep, NULL, &s1, &s2, &s3, &s4);
	if (ret == 0) {
		printf("Message %d - s:%s,s:%ss:%ss:%s\n", msgid,
		       s1, s2, s3 ? s3 : "(NULL)", s4 ? s4 : "(NULL)");
	}
	return ret;
}
