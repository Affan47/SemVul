mydbm_load_file (FILE *fp, List *list, char *filename)
{
    char *line = NULL;
    size_t line_size;
    char *value;
    size_t value_allocated;
    char *cp, *vp;
    int cont;
    int line_length;
    int line_num;

    value_allocated = 1;
    value = xmalloc (value_allocated);

    cont = 0;
    line_num=0;
    while ((line_length = getdelim (&line, &line_size, '\012', fp)) >= 0)
    {
	line_num++;
	if (line_length > 0 && line[line_length - 1] == '\012')
	{

	    --line_length;
	    line[line_length] = '\0';
	}
	if (line_length > 0 && line[line_length - 1] == '\015')
	{


	    --line_length;
	    line[line_length] = '\0';
	}


	if (!cont)
	    value[0] = '\0';


	if (line_length > 0)
	    cp = &line[line_length - 1];
	else
	    cp = line;
	if (*cp == '\\')
	{
	    cont = 1;
	    *cp = '\0';
	    --line_length;
	}
	else
	{
	    cont = 0;
	}
	expand_string (&value,
		       &value_allocated,
		       strlen (value) + line_length + 5);
	strcat (value, line);

	if (value[0] == '#')
	    continue;
	vp = value;
	while (*vp && isspace ((unsigned char) *vp))
	    vp++;
	if (*vp == '\0')
	    continue;


	if (!cont)
	{
	    Node *p = getnode ();
	    char *kp;

	    kp = vp;
	    while (*vp && !isspace ((unsigned char) *vp))
		vp++;
	    if (*vp)
		*vp++ = '\0';
	    p->type = NDBMNODE;
	    p->key = xstrdup (kp);
	    while (*vp && isspace ((unsigned char) *vp))
		vp++;
	    if (*vp == '\0')
	    {
		if (!really_quiet)
		    error (0, 0,
			"warning: NULL value for key `%s' at line %d of `%s'",
			p->key, line_num,
			primary_root_inverse_translate (filename));
		freenode (p);
		continue;
	    }
	    p->data = xstrdup (vp);
	    if (addnode (list, p) == -1)
	    {
		if (!really_quiet)
		    error (0, 0,
			"duplicate key found for `%s' at line %d of `%s'",
			p->key, line_num,
			primary_root_inverse_translate (filename));
		freenode (p);
	    }
	}
    }
    if (line_length < 0 && !feof (fp))
	error (0, errno, "cannot read file `%s' in mydbm_load_file",
	       primary_root_inverse_translate (filename));

    free (line);
    free (value);
}
