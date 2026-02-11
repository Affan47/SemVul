add_file_by_name(struct afp_file_info ** base, const char *filename)
{
	struct afp_file_info * t,*new_file;

	new_file=malloc(sizeof(*new_file));
	memcpy(new_file->name,filename,AFP_MAX_PATH);
	new_file->next=NULL;

	if (*base==NULL) {
		*base=new_file;
	} else {
		for (t=*base;t->next;t=t->next);
		t->next=new_file;
	}

}
