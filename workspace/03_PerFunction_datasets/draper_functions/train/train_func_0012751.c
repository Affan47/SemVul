ay_save_account_information(int service_id)
{
	LList *saved = NULL;
	LList *walk = NULL;

	for (walk = get_all_contacts(); walk; walk = walk->next) {
		struct contact *c = (struct contact *)walk->data;
		LList *accs = c->accounts;
		for (; accs; accs = accs->next) {
			eb_account *ea = (eb_account *)accs->data;
			if (service_id == -1 || ea->service_id == service_id) {
				account_information *ai =
					g_new0(account_information, 1);
				ai->ea = ea;
				if (ea->ela)
					ai->local_acc = strdup(ea->ela->handle);
				else
					ai->local_acc = NULL;
				eb_debug(DBG_CORE,
					" SAVED { %p(%s), %d, %s }\n", ea,
					ea->handle, ea->service_id,
					ea->ela ? ea->ela->handle : "NULL");
				saved = l_list_append(saved, ai);
			}
		}
	}
	return saved;
}
