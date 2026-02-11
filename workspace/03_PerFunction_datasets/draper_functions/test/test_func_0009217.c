create_attachment(char *file_name, char *message)
{
    PostAttachment	*pa;
    char		*c;

    message[0] = '\0';
    file_name = expand_path(file_name);
    if (!file_name) {
	strcpy(message, "File name error!");
	return NULL;
    }

    pa = (PostAttachment *)XtMalloc(sizeof *pa);
    pa->file_name = file_name;
    pa->type = NULL;
    pa->name = NULL;
    pa->descr = NULL;
    pa->is_inline = False;
    pa->enc = -1;
    pa->needs_enc = False;
    pa->has_8bit = False;

    if (!check_file(pa, message)) {
	free_attachment(pa);
	return NULL;
    }

    c = strrchr(file_name, '/');
    if (c)
	c++;
    else
	c = file_name;
    pa->name = XtNewString(c);

    return pa;
}
