free_rcsnode_contents (RCSNode *rnode)
{
    dellist (&rnode->versions);
    if (rnode->symbols != NULL)
	dellist (&rnode->symbols);
    if (rnode->symbols_data != NULL)
	free (rnode->symbols_data);
    if (rnode->expand != NULL)
	free (rnode->expand);
    if (rnode->other != NULL)
	dellist (&rnode->other);
    if (rnode->access != NULL)
	free (rnode->access);
    if (rnode->locks_data != NULL)
	free (rnode->locks_data);
    if (rnode->locks != NULL)
	dellist (&rnode->locks);
    if (rnode->comment != NULL)
	free (rnode->comment);
    if (rnode->desc != NULL)
	free (rnode->desc);
}
