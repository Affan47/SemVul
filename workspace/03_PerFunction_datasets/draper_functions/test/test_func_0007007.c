vm_jni_init_interface(void)
{
	jni_not_implemented_trap = alloc_guard_page(true);
	if (!jni_not_implemented_trap)
		die("guard page alloc failed");


	unsigned int table_size = ARRAY_SIZE(vm_jni_native_interface);
	for (unsigned int i = 0; i < table_size; i++) {
		if (vm_jni_native_interface[i])
			continue;

		vm_jni_native_interface[i] =
			jni_not_implemented_trap + i;
	}
}
