rb_trap_exit(void)
{
    rb_vm_t *vm = GET_VM();
    VALUE trap_exit = vm->trap_list[0].cmd;

    if (trap_exit) {
	vm->trap_list[0].cmd = 0;
	signal_exec(trap_exit, vm->trap_list[0].safe, 0);
    }
}
