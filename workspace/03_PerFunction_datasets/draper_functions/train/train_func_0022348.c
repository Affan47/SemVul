list_add(char *naming_context, char *name, void ***ptr)
{
  char *p;
  Dsvec *dsv;

  if ((dsv = (Dsvec *) *ptr) == NULL) {
	*ptr = (void **) dsvec_init(NULL, sizeof(char *));
	dsv = (Dsvec *) *ptr;
  }

  if (naming_context != NULL && (p = strprefix(name, naming_context)) != NULL)
	dsvec_add_ptr(dsv, strdup(p + 1));
  else
	dsvec_add_ptr(dsv, strdup(name));

  return(1);
}
