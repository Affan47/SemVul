fm6_write_smem(const rld_t *e, const fmintv_t *a, kstring_t *s)
{
	s->l = 0;
	kputuw(a->info>>32&FM_MASK30, s); kputc('\t', s); kputuw(a->info&FM_MASK30, s); kputc('\t', s);
	kputuw(a->x[2] > 0xffffffffU? 0xffffffffU : a->x[2], s); kputc('\t', s);
	kputc("OT"[a->info>>63], s); kputc("OT"[a->x[1] < e->mcnt[1]], s);
	return s->l;
}
