mkp_project_add_rule (MkpProject *project, AnjutaToken *group)
{
	AnjutaToken *targ;
	AnjutaToken *dep;
	AnjutaToken *arg;
	gboolean double_colon = FALSE;


	targ = anjuta_token_first_item (group);
	arg = anjuta_token_next_word (targ);
	if (anjuta_token_get_type (arg) == MK_TOKEN_DOUBLE_COLON) double_colon = TRUE;
	dep = anjuta_token_next_word (arg);
	for (arg = anjuta_token_first_word (targ); arg != NULL; arg = anjuta_token_next_word (arg))
	{
		AnjutaToken *src = NULL;
		gchar *target = NULL;
		gboolean order = FALSE;
		gboolean no_token = TRUE;
		MkpRule *rule = NULL;

		switch (anjuta_token_get_type (arg))
		{
		case MK_TOKEN__PHONY:
			for (src = anjuta_token_first_word (dep); src != NULL; src = anjuta_token_next_word (src))
			{
				if (anjuta_token_get_type (src) != MK_TOKEN_ORDER)
				{
					target = anjuta_token_evaluate (src);

					rule = g_hash_table_lookup (project->rules, target);
					if (rule == NULL)
					{
						rule = mkp_rule_new (target, NULL);
						g_hash_table_insert (project->rules, rule->name, rule);
					}
					rule->phony = TRUE;


					if (target != NULL) g_free (target);
				}
			}
			break;
		case MK_TOKEN__SUFFIXES:
			for (src = anjuta_token_first_word (dep); src != NULL; src = anjuta_token_next_word (src))
			{
				if (anjuta_token_get_type (src) != MK_TOKEN_ORDER)
				{
					gchar *suffix;

					suffix = anjuta_token_evaluate (src);


					g_hash_table_replace (project->suffix, suffix, suffix);

					no_token = FALSE;
				}
			}
			if (no_token == TRUE)
			{

				g_hash_table_remove_all (project->suffix);
			}
			break;
		case MK_TOKEN__DEFAULT:
		case MK_TOKEN__PRECIOUS:
		case MK_TOKEN__INTERMEDIATE:
		case MK_TOKEN__SECONDARY:
		case MK_TOKEN__SECONDEXPANSION:
		case MK_TOKEN__DELETE_ON_ERROR:
		case MK_TOKEN__IGNORE:
		case MK_TOKEN__LOW_RESOLUTION_TIME:
		case MK_TOKEN__SILENT:
		case MK_TOKEN__EXPORT_ALL_VARIABLES:
		case MK_TOKEN__NOTPARALLEL:

			break;
		default:
			target = g_strstrip (anjuta_token_evaluate (arg));
			if (*target == '\0') break;


			rule = g_hash_table_lookup (project->rules, target);
			if (rule == NULL)
			{
				rule = mkp_rule_new (target, group);
				g_hash_table_insert (project->rules, rule->name, rule);
			}
			else
			{
				rule->rule = group;
			}

			for (src = anjuta_token_first_word (dep); src != NULL; src = anjuta_token_next_word (src))
			{
				gchar *src_name = anjuta_token_evaluate (src);

				if (src_name != NULL)
				{

					if (anjuta_token_get_type (src) == MK_TOKEN_ORDER)
					{
						order = TRUE;
					}
					rule->prerequisite = g_list_prepend (rule->prerequisite, src_name);
				}
			}

			if (target != NULL) g_free (target);
		}
	}
}
