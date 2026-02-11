vm_jni_get_java_vm(struct vm_jni_env *env, struct java_vm **vm)
{
	enter_vm_from_jni();

	*vm = vm_jni_get_current_java_vm();
	return 0;
}
