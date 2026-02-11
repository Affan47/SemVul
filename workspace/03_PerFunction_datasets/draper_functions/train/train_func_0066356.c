new_cons_pointer(struct alisp_instance * instance, const char *ptr_id, void *ptr)
{
	struct alisp_object * lexpr;

	if (ptr == NULL)
		return &alsa_lisp_nil;
	lexpr = new_object(instance, ALISP_OBJ_CONS);
	if (lexpr == NULL)
		return NULL;
	lexpr->value.c.car = new_string(instance, ptr_id);
	if (lexpr->value.c.car == NULL)
		goto __end;
	lexpr->value.c.cdr = new_pointer(instance, ptr);
	if (lexpr->value.c.cdr == NULL) {
		delete_object(instance, lexpr->value.c.car);
	      __end:
		delete_object(instance, lexpr);
		return NULL;
	}
	return lexpr;
}
