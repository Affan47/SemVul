expand_variable (const char *name, const char *cvsroot,
		 const char *file, int line)
{
    if (!strcmp (name, CVSROOT_ENV))
	return cvsroot;
    else if (!strcmp (name, "RCSBIN"))
    {
	error (0, 0, "RCSBIN internal variable is no longer supported");
	return NULL;
    }
    else if (!strcmp (name, EDITOR1_ENV))
	return Editor;
    else if (!strcmp (name, EDITOR2_ENV))
	return Editor;
    else if (!strcmp (name, EDITOR3_ENV))
	return Editor;
    else if (!strcmp (name, "USER"))
	return getcaller ();
    else if (!strcmp (name, "SESSIONID")
	     || !strcmp (name, "COMMITID"))
	return global_session_id;
    else if (isalpha (name[0]))
    {


	if (line)
	    error (0, 0, "%s:%d: no such internal variable $%s",
		   file, line, name);
	else
	    error (0, 0, "%s: no such internal variable $%s",
		   file, name);
	return NULL;
    }
    else if (name[0] == '=')
    {
	Node *node;


	node = findnode (variable_list, name + 1);
	if (!node)
	{
	    if (line)
		error (0, 0, "%s:%d: no such user variable ${%s}",
		       file, line, name);
	    else
		error (0, 0, "%s: no such user variable ${%s}",
		       file, name);
	    return NULL;
	}
	return node->data;
    }
    else
    {


	if (line)
	    error (0, 0, "%s:%d: unrecognized variable syntax %s",
		   file, line, name);
	else
	    error (0, 0, "%s: unrecognized variable syntax %s",
		   file, name);
	return NULL;
    }
}
