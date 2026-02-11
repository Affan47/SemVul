db_search_dbn(struct dbt *table,void *key)
{
	struct dbn *p;

	if( table == NULL ) return NULL;

	for(p=table->ht[table->hash(table,key) % HASH_SIZE];p;){
		int c=table->cmp(table,key,p->key);
		if(c==0)
			return p;
		if(c<0)
			p=p->left;
		else
			p=p->right;
	}
	return NULL;
}
