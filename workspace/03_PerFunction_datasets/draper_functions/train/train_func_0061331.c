print_orglist(struct prog_info *pi)
{
	struct orglist *orglist=pi->first_orglist;
	printf("Used memory blocks:\n");
	while(orglist!=NULL) {
		if(orglist->length) {
			switch(orglist->segment) {
				case SEGMENT_CODE:
					printf("   Code  "); break;
				case SEGMENT_DATA:
					printf("   Data  "); break;
				case SEGMENT_EEPROM:
					printf("   EEPROM"); break;
				printf("INVALID SEGMENT DATA !\n");
			}
			printf("    :  Start = 0x%04X, End = 0x%04X, Length = 0x%04X\n",
				orglist->start,orglist->start+orglist->length-1,orglist->length);
		}
		orglist=orglist->next;
	}
}
