plugin_hook_run (session *sess, char *name, char *word[], char *word_eol[],
				 hexchat_event_attrs *attrs, int type)
{
	GSList *list, *next;
	hexchat_hook *hook;
	int ret, eat = 0;

	list = hook_list;
	while (1)
	{
		list = plugin_hook_find (list, type, name);
		if (!list)
			goto xit;

		hook = list->data;
		next = list->next;
		hook->pl->context = sess;


		switch (type)
		{
		case HOOK_COMMAND:
			ret = ((hexchat_cmd_cb *)hook->callback) (word, word_eol, hook->userdata);
			break;
		case HOOK_PRINT_ATTRS:
			ret = ((hexchat_print_attrs_cb *)hook->callback) (word, attrs, hook->userdata);
			break;
		case HOOK_SERVER:
			ret = ((hexchat_serv_cb *)hook->callback) (word, word_eol, hook->userdata);
			break;
		case HOOK_SERVER_ATTRS:
			ret = ((hexchat_serv_attrs_cb *)hook->callback) (word, word_eol, attrs, hook->userdata);
			break;
		default:
			ret = ((hexchat_print_cb *)hook->callback) (word, hook->userdata);
			break;
		}

		if ((ret & HEXCHAT_EAT_HEXCHAT) && (ret & HEXCHAT_EAT_PLUGIN))
		{
			eat = 1;
			goto xit;
		}
		if (ret & HEXCHAT_EAT_PLUGIN)
			goto xit;
		if (ret & HEXCHAT_EAT_HEXCHAT)
			eat = 1;

		list = next;
	}

xit:

	list = hook_list;
	while (list)
	{
		hook = list->data;
		next = list->next;
		if (!hook || hook->type == HOOK_DELETED)
		{
			hook_list = g_slist_remove (hook_list, hook);
			free (hook);
		}
		list = next;
	}

	return eat;
}
