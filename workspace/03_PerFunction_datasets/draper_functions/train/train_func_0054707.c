rb_frame_caller(void)
{
    rb_thread_t *th = GET_THREAD();
    rb_control_frame_t *prev_cfp = RUBY_VM_PREVIOUS_CONTROL_FRAME(th->cfp);

    if ((void *)(th->stack + th->stack_size) == (void *)(prev_cfp)) {
        return 0;
    }
    return frame_func_id(prev_cfp);
}
