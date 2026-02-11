parse_imap_mail_args(struct text_object *obj, const char *arg)
{
	static int rep = 0;

	if (!arg) {
		if (!global_mail && !rep) {

			NORM_ERR("There's a problem with your mail settings.  "
					"Check that the global mail settings are properly defined"
					" (line %li).", obj->line);
			rep = 1;
			return;
		}
		obj->data.opaque = global_mail;
		global_mail_use++;
		return;
	}

	obj->data.opaque = parse_mail_args(IMAP_TYPE, arg);
}
