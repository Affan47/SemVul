bam_list_size(const bam_list * list)
{
	BAM_TRACE("bam_list_size(list) {\n");

	int i;

	if(list == NULL)
		return 0;

	for(i=0; list != NULL; i++)
		list = list->next;

	BAM_TRACE("} //bam_list_size(list)\n");

	return i;
}
