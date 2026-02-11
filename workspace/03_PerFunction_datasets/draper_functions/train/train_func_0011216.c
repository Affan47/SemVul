fax_session_reserve(struct ast_fax_session_details *details, struct ast_fax_tech_token **token)
{
	struct ast_fax_session *s;
	struct fax_module *faxmod;

	if (!(s = ao2_alloc(sizeof(*s), destroy_session))) {
		return NULL;
	}

	s->state = AST_FAX_STATE_INACTIVE;
	s->details = details;
	ao2_ref(s->details, 1);


	AST_RWLIST_RDLOCK(&faxmodules);
	AST_RWLIST_TRAVERSE(&faxmodules, faxmod, list) {
		if ((faxmod->tech->caps & details->caps) != details->caps) {
			continue;
		}
		ast_debug(4, "Reserving a FAX session from '%s'.\n", faxmod->tech->description);
		ast_module_ref(faxmod->tech->module);
		s->tech = faxmod->tech;
		break;
	}
	AST_RWLIST_UNLOCK(&faxmodules);

	if (!faxmod) {
		char caps[128] = "";
		ast_log(LOG_ERROR, "Could not locate a FAX technology module with capabilities (%s)\n", ast_fax_caps_to_str(details->caps, caps, sizeof(caps)));
		ao2_ref(s, -1);
		return NULL;
	}

	if (!s->tech->reserve_session) {
		ast_debug(1, "Selected FAX technology module (%s) does not support reserving sessions.\n", s->tech->description);
		return s;
	}

	if (!(*token = s->tech->reserve_session(s))) {
		ao2_ref(s, -1);
		return NULL;
	}

	s->state = AST_FAX_STATE_RESERVED;
	ast_atomic_fetchadd_int(&faxregistry.reserved_sessions, 1);

	return s;
}
