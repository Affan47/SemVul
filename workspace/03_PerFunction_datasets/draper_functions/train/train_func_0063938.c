debug_print_vm_object(struct vm_object *obj)
{
	if (obj) {
		printf("vm_object address : %p\n", obj);
		debug_print_vm_class(obj->class);
	} else {
		printf("Unable to print null vm_object!\n");
	}
}
