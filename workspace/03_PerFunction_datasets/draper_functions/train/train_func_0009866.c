env_free(hx509_env b)
{
    while(b) {
	hx509_env next = b->next;

	if (b->type == env_string)
	    free(b->u.string);
	else if (b->type == env_list)
	    env_free(b->u.list);

	free(b->name);
	free(b);
	b = next;
    }
}
