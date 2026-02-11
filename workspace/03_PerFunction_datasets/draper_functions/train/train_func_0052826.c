imap_do_auth(struct sasl_cmd_t *sasl_cmd,
			void *rock __attribute__((unused)),
			int login_enabled,
			char *mech, char *mechlist)
{
    int result = IMTEST_FAIL;

    if (mech) {
	if (!strcasecmp(mech, "login")) {
	    if (!login_enabled) {
		printf("[Server advertised LOGINDISABLED]\n");
	    } else {
		result = auth_imap();
	    }
	} else if (!mechlist || !stristr(mechlist, mech)) {
	    printf("[Server did not advertise AUTH=%s]\n", ucase(mech));
	} else {
	    result = auth_sasl(sasl_cmd, mech);
	}
    } else {
	if (mechlist) {
	    result = auth_sasl(sasl_cmd, mechlist);
	} else if (login_enabled) {
	    result = auth_imap();
	}
    }

    return result;
}
