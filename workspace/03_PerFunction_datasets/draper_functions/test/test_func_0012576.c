Init_BareVM(void)
{

    rb_vm_t * vm = malloc(sizeof(*vm));
    rb_thread_t * th = malloc(sizeof(*th));
    if (!vm || !th) {
	fprintf(stderr, "[FATAL] failed to allocate memory\n");
	exit(EXIT_FAILURE);
    }
    MEMZERO(th, rb_thread_t, 1);

    rb_thread_set_current_raw(th);

    vm_init2(vm);
#if defined(ENABLE_VM_OBJSPACE) && ENABLE_VM_OBJSPACE
    vm->objspace = rb_objspace_alloc();
#endif
    ruby_current_vm = vm;

    Init_native_thread();
    th_init(th, 0);
    th->vm = vm;
    ruby_thread_init_stack(th);
}
