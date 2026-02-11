get_object(struct alisp_instance *instance, struct alisp_object * name)
{
	if (!alisp_compare_type(name, ALISP_OBJ_IDENTIFIER) &&
	    !alisp_compare_type(name, ALISP_OBJ_STRING)) {
	    	delete_tree(instance, name);
		return &alsa_lisp_nil;
	}
	return get_object1(instance, name->value.s);
}
