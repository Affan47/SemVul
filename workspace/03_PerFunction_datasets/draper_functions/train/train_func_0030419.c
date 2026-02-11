mono_arch_notify_pending_exc (void)
{
	MonoLMF *lmf = mono_get_lmf ();

	if (!lmf)

		return;

	if (lmf->rsp == 0)

		return;

	if ((guint64)lmf->previous_lmf & 1)

		return;


	lmf->rip = *(guint64*)(lmf->rsp - 8);

	lmf->previous_lmf = (gpointer)((guint64)lmf->previous_lmf | 1);

	*(gpointer*)(lmf->rsp - 8) = throw_pending_exception;
}
