attr_list_pack(const char *name, const int valuelen,
		char *buffer, const int buffersize,
		int *start_offset, int *end_offset)
{
	attrlist_ent_t *aentp;
	attrlist_t *alist = (attrlist_t *)buffer;
	int size = roundup(strlen(name) + 1 + sizeof(aentp->a_valuelen), 8);

	if ((*end_offset - size) < (*start_offset + sizeof(alist->al_count))) {
		alist->al_more = 1;
		return 1;
	}

	*end_offset -= size;
	aentp = (attrlist_ent_t *)&buffer[ *end_offset ];
	aentp->a_valuelen = valuelen;
	strncpy(aentp->a_name, name, size - sizeof(aentp->a_valuelen));

	*start_offset += sizeof(alist->al_offset);
	alist->al_offset[alist->al_count] = *end_offset;
	alist->al_count++;
	return 0;
}
