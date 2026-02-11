off_history(struct Client *client_p)
{
	struct Whowas *temp, *next;

	for(temp = client_p->whowas; temp; temp = next)
	{
		next = temp->cnext;
		temp->online = NULL;
		del_whowas_from_clist(&(client_p->whowas), temp);
	}
}
