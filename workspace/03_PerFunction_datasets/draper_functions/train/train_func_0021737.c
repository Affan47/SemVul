smp_fetch_len(struct proxy *px, struct session *s, void *l7, unsigned int opt,
                  const struct arg *args, struct sample *smp, const char *kw)
{
	struct channel *chn = ((opt & SMP_OPT_DIR) == SMP_OPT_DIR_RES) ? s->rep : s->req;

	if (!s || !chn)
		return 0;

	smp->type = SMP_T_UINT;
	smp->data.uint = chn->buf->i;
	smp->flags = SMP_F_VOLATILE | SMP_F_MAY_CHANGE;
	return 1;
}
