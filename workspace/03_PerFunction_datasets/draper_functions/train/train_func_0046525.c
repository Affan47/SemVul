copy_str_list(struct idlist *idl)
{
    struct idlist *newnode ;

    if (idl == (struct idlist *)NULL)
	return(NULL);
    else
    {
	newnode = (struct idlist *)xmalloc(sizeof(struct idlist));
	memcpy(newnode, idl, sizeof(struct idlist));
	newnode->next = copy_str_list(idl->next);
	return(newnode);
    }
}
