add_server_to_tree(aClient *acptr)
{
	acptr->serv->up->serv->servers++;

	if (acptr->serv->up->serv->down)
	{
		acptr->serv->up->serv->down->serv->left = acptr;
	}

	acptr->serv->right = acptr->serv->up->serv->down;
	acptr->serv->up->serv->down = acptr;

	return;
}
