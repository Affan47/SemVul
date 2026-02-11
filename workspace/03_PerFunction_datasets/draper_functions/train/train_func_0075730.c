ml_close(buf)
	BUF		*buf;
{
	if (buf->b_ml.ml_mfp == NULL)
		return;
	mf_close(buf->b_ml.ml_mfp, TRUE);
	if (buf->b_ml.ml_line_lnum != 0 && (buf->b_ml.ml_flags & ML_LINE_DIRTY))
		free(buf->b_ml.ml_line_ptr);
	free(buf->b_ml.ml_stack);
	buf->b_ml.ml_mfp = NULL;
#if defined(NT) && defined(USE_EXFILE) && defined(USE_SHARE_CHECK)
	ef_share_close(buf->b_filename);
#endif
#if defined(NT) && defined(USE_HISTORY)
	win_history_append(buf);
#endif
}
