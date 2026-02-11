display_avdecl(avrule_decl_t * decl, int field,
		   policydb_t * policy, FILE * out_fp)
{
	fprintf(out_fp, "decl %u:%s\n", decl->decl_id,
		(decl->enabled ? " [enabled]" : ""));
	switch (field) {
	case DISPLAY_AVBLOCK_COND_AVTAB:{
			cond_list_t *cond = decl->cond_list;
			avrule_t *avrule;
			while (cond) {
				fprintf(out_fp, "expression: ");
				display_expr(&policydb, cond->expr, out_fp);
				fprintf(out_fp, "current state: %d\n",
					cond->cur_state);
				fprintf(out_fp, "True list:\n");
				avrule = cond->avtrue_list;
				while (avrule) {
					display_avrule(avrule,
						       &policydb, out_fp);
					avrule = avrule->next;
				}
				fprintf(out_fp, "False list:\n");
				avrule = cond->avfalse_list;
				while (avrule) {
					display_avrule(avrule,
						       &policydb, out_fp);
					avrule = avrule->next;
				}
				cond = cond->next;
			}
			break;
		}
	case DISPLAY_AVBLOCK_UNCOND_AVTAB:{
			avrule_t *avrule = decl->avrules;
			if (avrule == NULL) {
				fprintf(out_fp, "  <empty>\n");
			}
			while (avrule != NULL) {
				if (display_avrule(avrule, policy, out_fp))
					return -1;
				avrule = avrule->next;
			}
			break;
		}
	case DISPLAY_AVBLOCK_ROLE_TYPE_NODE:{
			break;
		}
	case DISPLAY_AVBLOCK_ROLE_TRANS:{
			display_role_trans(decl->role_tr_rules, policy, out_fp);
			break;
		}
	case DISPLAY_AVBLOCK_ROLE_ALLOW:{
			display_role_allow(decl->role_allow_rules, policy,
					   out_fp);
			break;
		}
	case DISPLAY_AVBLOCK_REQUIRES:{
			if (display_scope_index
			    (&decl->required, policy, out_fp)) {
				return -1;
			}
			break;
		}
	case DISPLAY_AVBLOCK_DECLARES:{
			if (display_scope_index
			    (&decl->declared, policy, out_fp)) {
				return -1;
			}
			break;
		}
	case DISPLAY_AVBLOCK_FILENAME_TRANS:
		display_filename_trans(decl->filename_trans_rules, policy,
				       out_fp);
		break;
	default:{
			assert(0);
		}
	}
	return 0;
}
