wipe_dummy_buffer(buf)
    buf_T	*buf;
{
    if (curbuf != buf)
    {
#if defined(FEAT_AUTOCMD) && defined(FEAT_EVAL)
	cleanup_T   cs;


	enter_cleanup(&cs);
#endif

	wipe_buffer(buf, FALSE);

#if defined(FEAT_AUTOCMD) && defined(FEAT_EVAL)


	leave_cleanup(&cs);
#endif
    }
}
