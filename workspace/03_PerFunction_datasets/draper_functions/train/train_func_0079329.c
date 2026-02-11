finding_closure(vm the_vm, const char *status, void *data)
{
    struct fcl_data *fdata = data;

    if (the_vm->task_id == fdata->id) {
	fdata->the_vm = the_vm;
	return TEA_STOP;
    }
    return TEA_CONTINUE;
}
