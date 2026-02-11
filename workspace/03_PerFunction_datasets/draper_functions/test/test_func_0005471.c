search_netrc (netrc_entry *list, char *host, char *login)
{

    while (list)
    {
	if (list->host && !strcmp(list->host, host))
	    if (!list->login || !strcmp(list->login, login))

		break;

	list = list->next;
    }


    return list;
}
