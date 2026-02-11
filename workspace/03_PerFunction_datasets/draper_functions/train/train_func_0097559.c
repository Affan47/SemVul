count_java_arguments(const struct vm_method *vmm)
{
	struct vm_method_arg *arg;
	unsigned int count;

	count = 0;
	list_for_each_entry(arg, &vmm->args, list_node) {
		count++;
	}

	return count;
}
