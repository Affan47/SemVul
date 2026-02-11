vm_unregister_natives(void)
{
	unsigned long i;

	for (i = 0; i < nr_natives; i++) {
		struct vm_class *class = native_methods + i;

		free(class->method_ptrs);
	}
	free(native_methods);
	native_methods = NULL;
	nr_natives = 0;
}
