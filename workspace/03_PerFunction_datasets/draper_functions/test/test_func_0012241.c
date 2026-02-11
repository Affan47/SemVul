_acl_cleanup(struct mosquitto_db *db, bool reload)
{
	int i;
	struct _mosquitto_acl_user *user_tail;

	if(!db) return MOSQ_ERR_INVAL;
	if(!db->acl_list) return MOSQ_ERR_SUCCESS;


	if(db->contexts){
		for(i=0; i<db->context_count; i++){
			if(db->contexts[i] && db->contexts[i]->acl_list){
				db->contexts[i]->acl_list = NULL;
			}
		}
	}

	while(db->acl_list){
		user_tail = db->acl_list->next;

		_free_acl(db->acl_list->acl);
		if(db->acl_list->username){
			_mosquitto_free(db->acl_list->username);
		}
		_mosquitto_free(db->acl_list);

		db->acl_list = user_tail;
	}

	if(db->acl_patterns){
		_free_acl(db->acl_patterns);
		db->acl_patterns = NULL;
	}
	return MOSQ_ERR_SUCCESS;
}
