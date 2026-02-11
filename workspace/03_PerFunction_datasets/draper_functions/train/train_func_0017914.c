log_updates( struct nvpair_database *db, const char *key, struct nvpair *a, struct nvpair *b )
{
	log_select(db);

	char *name, *avalue, *bvalue;


	hash_table_firstkey(a->table);
	while(hash_table_nextkey(a->table,&name,(void**)&avalue)) {


		if(!strcmp(name,"lastheardfrom")) continue;
		if(!strcmp(name,"uptime")) continue;

		bvalue = hash_table_lookup(b->table,name);
		if(bvalue) {
			if(!strcmp(avalue,bvalue)) {

			} else {
				log_time(db);
				fprintf(db->logfile,"U %s %s %s\n",key,name,bvalue);
			}
		} else {
       			log_time(db);
			fprintf(db->logfile,"R %s %s\n",key,name);
		}
	}


	hash_table_firstkey(b->table);
	while(hash_table_nextkey(b->table,&name,(void**)&bvalue)) {
		avalue = hash_table_lookup(a->table,name);
		if(!avalue) {
       			log_time(db);
			fprintf(db->logfile,"U %s %s %s\n",key,name,bvalue);
		}
	}
}
