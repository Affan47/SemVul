NewDictionary()
{
 	int i;
	_Dictionary *dict;

  	dict = (_Dictionary*)MALLOC(sizeof(_Dictionary));
   	if (!dict)
	    return NULL;
	if (!(dict->harr = (DictItem**)MALLOC(HASH_SIZE*sizeof(DictItem*))))
	    return NULL;
	dict->num_in_dict = 0;
	dict->size = HASH_SIZE;
	for (i=0 ; i<HASH_SIZE; i++)
		dict->harr[i] = (DictItem*)NULL;

	return(dict);
}
