remove_user (CONNECTION * con)
{
    LIST   *u;

    ASSERT (ISUSER (con));

    if (con->user->level >= LEVEL_MODERATOR)
	Mods = list_delete (Mods, con);


    ASSERT (validate_user (con->user));
    hash_remove (Users, con->user->nick);


    for (u = con->uopt->hotlist; u; u = u->next)
    {
	ASSERT (hashlist_validate (u->data));
	hashlist_remove (Hotlist, ((hashlist_t *) u->data)->key, con);
    }

    list_free (con->uopt->hotlist, 0);
    list_free (con->uopt->ignore, free_pointer);

    if (con->uopt->files)
    {

	free_hash (con->uopt->files);
    }


    if (con->uopt->searches < 0)
	log_message("remove_user: ERROR, con->uopt->searches < 0!!!");

    FREE (con->uopt);
}
