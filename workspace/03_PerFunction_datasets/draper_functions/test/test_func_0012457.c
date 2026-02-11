sspm_parse_mime(struct sspm_part *parts,
		    size_t max_parts,
		    const struct sspm_action_map *actions,
		    char* (*get_string)(char *s, size_t size, void* data),
		    void *get_string_data,
		    struct sspm_header *first_header
    )
{
    struct mime_impl impl;
    struct sspm_header header;
    void *part;
    int i;
    (void)first_header;


    memset(&impl,0,sizeof(struct mime_impl));
    memset(&header,0,sizeof(struct sspm_header));

    for(i = 0; i<(int)max_parts; i++){
	parts[i].header.major = SSPM_NO_MAJOR_TYPE;
	parts[i].header.minor = SSPM_NO_MINOR_TYPE;
    }

    impl.parts = parts;
    impl.max_parts = max_parts;
    impl.part_no = 0;
    impl.actions = actions;
    impl.get_string = get_string;
    impl.get_string_data = get_string_data;


    sspm_read_header(&impl,&header);

    if(header.major == SSPM_MULTIPART_MAJOR_TYPE){
	struct sspm_header *child_header;
	child_header = &(impl.parts[impl.part_no].header);

	sspm_store_part(&impl,header,impl.level,0,0);

	part = sspm_make_multipart_part(&impl,child_header);

    } else {
	void *part;
	size_t size;
	sspm_make_part(&impl, &header, 0,&part,&size);

	memset(&(impl.parts[impl.part_no]), 0, sizeof(struct sspm_part));

	sspm_store_part(&impl,header,impl.level,part,size);
    }

    return 0;
}
