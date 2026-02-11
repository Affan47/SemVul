switch_modifier(snd_use_case_mgr_t *uc_mgr,
                           const char *old_modifier,
                           const char *new_modifier)
{
        struct use_case_modifier *xold, *xnew;
        struct transition_sequence *trans;
        struct list_head *pos;
        int err, seq_found = 0;

        if (uc_mgr->active_verb == NULL)
                return -ENOENT;
        if (modifier_status(uc_mgr, old_modifier) == 0) {
                uc_error("error: modifier %s not enabled", old_modifier);
                return -EINVAL;
        }
        if (modifier_status(uc_mgr, new_modifier) != 0) {
                uc_error("error: modifier %s already enabled", new_modifier);
                return -EINVAL;
        }
        xold = find_modifier(uc_mgr, old_modifier);
        if (xold == NULL)
                return -ENOENT;
        xnew = find_modifier(uc_mgr, new_modifier);
        if (xnew == NULL)
                return -ENOENT;
        err = 0;
        list_for_each(pos, &xold->transition_list) {
                trans = list_entry(pos, struct transition_sequence, list);
                if (strcmp(trans->name, new_modifier) == 0) {
                        err = execute_sequence(uc_mgr, &trans->transition_list,
					       &xold->value_list,
					       &uc_mgr->active_verb->value_list,
					       &uc_mgr->value_list);
                        if (err >= 0) {
                                list_del(&xold->active_list);
                                list_add_tail(&xnew->active_list, &uc_mgr->active_modifiers);
                        }
                        seq_found = 1;
                        break;
                }
        }
        if (!seq_found) {
                err = set_modifier(uc_mgr, xold, 0);
                if (err < 0)
                        return err;
                err = set_modifier(uc_mgr, xnew, 1);
                if (err < 0)
                        return err;
        }
        return err;
}
