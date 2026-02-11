set_user(enum grecs_callback_command cmd,
	 grecs_locus_t *locus,
	 void *varptr,
	 grecs_value_t *value,
	 void *cb_data)
{
    struct passwd *pw;

    if (cmd != grecs_callback_set_value) {
	grecs_error(locus, 0, _("Unexpected block statement"));
	return 1;
    }

    if (value->type != GRECS_TYPE_STRING) {
	grecs_error(locus, 0, _("expected scalar value but found list"));
	return 1;
    }

    pw = getpwnam(value->v.string);
    if (!pw) {
	grecs_error(locus, 0, _("%s: no such user"), value->v.string);
	return 1;
    }
    user_id = pw->pw_uid;
    group_id = pw->pw_gid;
    return 0;
}
