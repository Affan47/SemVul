new_x_NC_dim(NC_string *name)
{
	NC_dim *dimp;

	dimp = (NC_dim *) malloc(sizeof(NC_dim));
	if(dimp == NULL)
		return NULL;

	dimp->name = name;
 	dimp->hash = hash_fast(name->cp, strlen(name->cp));
	dimp->size = 0;

	return(dimp);
}
