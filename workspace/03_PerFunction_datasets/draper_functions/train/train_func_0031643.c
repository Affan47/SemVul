snd_use_case_get(snd_use_case_mgr_t *uc_mgr,
		     const char *identifier,
		     const char **value)
{
        char *str, *str1;
        int err;

	pthread_mutex_lock(&uc_mgr->mutex);
	if (identifier == NULL) {
	        *value = strdup(uc_mgr->card_name);
	        if (*value == NULL) {
	                err = -ENOMEM;
	                goto __end;
                }
                err = 0;
        } else if (strcmp(identifier, "_verb") == 0) {
                if (uc_mgr->active_verb == NULL)
                        return -ENOENT;
                *value = strdup(uc_mgr->active_verb->name);
                if (*value == NULL) {
                        err = -ENOMEM;
                        goto __end;
                }
	        err = 0;
        } else {
                str1 = strchr(identifier, '/');
                if (str1) {
                        str = strdup(str1 + 1);
                	if (str == NULL) {
                  		err = -ENOMEM;
                		goto __end;
                        }
                } else {
                        str = NULL;
                }
                err = get_value(uc_mgr, identifier, value, str);
                if (str)
                        free(str);
        }
      __end:
	pthread_mutex_unlock(&uc_mgr->mutex);
        return err;
}
