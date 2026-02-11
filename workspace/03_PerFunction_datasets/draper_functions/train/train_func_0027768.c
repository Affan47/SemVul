func(void *arg, dir_walk_message_ty msg, string_ty *path,
    const struct stat *st)
{


    auxilliary *aux = (auxilliary *)arg;
    if (st->st_uid != aux->uid)
	return;


    mode_t mode = (st->st_mode & 07777) | 0644;
    if (S_ISDIR(st->st_mode))
	mode |= 0111;
    if (aux->protect)
	mode &= ~0222;
    mode &= ~aux->umask;


    switch (msg)
    {
    case dir_walk_dir_before:
    case dir_walk_special:
    case dir_walk_symlink:
	break;

    case dir_walk_dir_after:
	if ((st->st_mode & 07777) != mode)
	{
	    undo_chmod(path, st->st_mode & 07777);
	    os_chmod_errok(path, mode);
	}
	break;

    case dir_walk_file:
	if (st->st_nlink > 1)
	{


	    break;
	}


	aux->up->become_end();
	string_ty *rpath = os_below_dir(aux->dd, path);
	fstate_src_ty *src = change_file_find(aux->cp, rpath, view_path_first);
	if (src)
	{
	    switch (src->action)
	    {
	    case file_action_remove:

		break;

	    case file_action_insulate:
	    case file_action_transparent:
		mode &= ~0222;
		break;

	    case file_action_create:
	    case file_action_modify:
		break;
	    }
	}
	else
	{


	    src = project_file_find(aux->cp->pp, rpath, view_path_simple);
	    if (src)
		mode &= ~0222;
	}
	str_free(rpath);
	aux->up->become_begin();


	if ((st->st_mode & 07777) != mode)
	{
	    undo_chmod(path, st->st_mode & 07777);
	    os_chmod_errok(path, mode);
	}
	break;
    }
}
