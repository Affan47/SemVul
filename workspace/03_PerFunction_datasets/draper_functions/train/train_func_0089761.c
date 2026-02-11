rb_sourcefile(void)
{
    rb_thread_t *th = GET_THREAD();
    rb_control_frame_t *cfp = rb_vm_get_ruby_level_next_cfp(th, th->cfp);

    if (cfp) {
	return RSTRING_PTR(cfp->iseq->filename);
    }
    else {
	return 0;
    }
}
