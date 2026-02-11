fxt_load_symbols( fxt_t fxt, FILE *fstream )
	{

	struct address_entry	*entry;
	char *name;
restart:
	if( !(entry = malloc(sizeof(*entry))) )
		{
		perror("allocating System map entry");
		return -1;
		}
	READ(64,entry->address);
	if( !entry->address )
		{
		free(entry);
		return 0;
		}


	READ(32,entry->len);
	if( !(name = malloc(entry->len+1)) )
		{
		perror("allocating System map entry name");
		return -1;
		}
	if( entry->len && fread(name, 1, entry->len, fstream) < entry->len )
		{
		perror("reading System map name");
		return -1;
		}

	name[entry->len]='\0';
	entry->name=name;
	entry->next=fxt->addresses[entry->address%NAMEHASH_ENTRIES];
	fxt->addresses[entry->address%NAMEHASH_ENTRIES]=entry;

	goto restart;
	}
