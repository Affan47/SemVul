switch_device(snd_use_case_mgr_t *uc_mgr,
                         const char *old_device,
                         const char *new_device)
{
        struct use_case_device *xold, *xnew;
        struct transition_sequence *trans;
        struct list_head *pos;
        int err, seq_found = 0;

        if (uc_mgr->active_verb == NULL)
                return -ENOENT;
        if (device_status(uc_mgr, old_device) == 0) {
                uc_error("error: device %s not enabled", old_device);
                return -EINVAL;
        }
        if (device_status(uc_mgr, new_device) != 0) {
                uc_error("error: device %s already enabled", new_device);
                return -EINVAL;
        }
        xold = find_device(uc_mgr->active_verb, old_device);
        if (xold == NULL)
                return -ENOENT;
        xnew = find_device(uc_mgr->active_verb, new_device);
        if (xnew == NULL)
                return -ENOENT;
        err = 0;
        list_for_each(pos, &xold->transition_list) {
                trans = list_entry(pos, struct transition_sequence, list);
                if (strcmp(trans->name, new_device) == 0) {
                        err = execute_sequence(uc_mgr, &trans->transition_list,
					       &xold->value_list,
					       &uc_mgr->active_verb->value_list,
					       &uc_mgr->value_list);
                        if (err >= 0) {
                                list_del(&xold->active_list);
                                list_add_tail(&xnew->active_list, &uc_mgr->active_devices);
                        }
                        seq_found = 1;
                        break;
                }
        }
        if (!seq_found) {
                err = set_device(uc_mgr, xold, 0);
                if (err < 0)
                        return err;
                err = set_device(uc_mgr, xnew, 1);
                if (err < 0)
                        return err;
        }
        return err;
}
