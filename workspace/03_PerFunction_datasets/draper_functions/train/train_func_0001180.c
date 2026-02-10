suspend_task(package p)
{
    vm the_vm = new_vm(current_task_id, var_ref(current_local), top_activ_stack + 1);
    int i;
    enum error e;

    the_vm->max_stack_size = max_stack_size;
    the_vm->top_activ_stack = top_activ_stack;
    the_vm->root_activ_vector = root_activ_vector;
    the_vm->func_id = 0;
    for (i = 0; i <= top_activ_stack; i++)
	the_vm->activ_stack[i] = activ_stack[i];

    e = (*p.u.susp.proc) (the_vm, p.u.susp.data);
    if (e != E_NONE)
	free_vm(the_vm, 0);
    return e;
}
