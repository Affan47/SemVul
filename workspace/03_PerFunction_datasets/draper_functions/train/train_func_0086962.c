vget_next(krb5_context context,
	  const krb5_config_binding *b,
	  const krb5_config_binding **pointer,
	  int type,
	  const char *name,
	  va_list args)
{
    const char *p = va_arg(args, const char *);
    while(b != NULL) {
	if(strcmp(b->name, name) == 0) {
	    if(b->type == (unsigned)type && p == NULL) {
		*pointer = b;
		return b->u.generic;
	    } else if(b->type == krb5_config_list && p != NULL) {
		return vget_next(context, b->u.list, pointer, type, p, args);
	    }
	}
	b = b->next;
    }
    return NULL;
}
