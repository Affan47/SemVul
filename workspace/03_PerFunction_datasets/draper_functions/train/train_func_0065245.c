find_two_masks(char *name, char *host, int stat)
{
	aConfItem *tmp;

	for (tmp = conf; tmp; tmp = tmp->next)
 		if ((tmp->status == stat) && tmp->host && tmp->name &&
		    (match(tmp->host, host) == 0) &&
 		    (match(tmp->name, name) == 0))
			break;
 	return (tmp ? -1 : 0);
}
