string_assign_null(struct string* dest)
{
	if(dest) {
		string_free(dest);
		dest->data=empty_string;
		dest->refcount=-1;
		dest->ref=NULL;
	}
}
