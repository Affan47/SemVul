VEP_Init(const struct sess *sp, vep_callback_t *cb)
{
	struct vep_state *vep;

	AZ(sp->wrk->vep);
	sp->wrk->vep = (void*)WS_Alloc(sp->wrk->ws, sizeof *vep);
	AN(sp->wrk->vep);

	vep = sp->wrk->vep;
	memset(vep, 0, sizeof *vep);
	vep->magic = VEP_MAGIC;
	vep->sp = sp;
	vep->vsb = VSB_new_auto();
	AN(vep->vsb);

	if (cb != NULL) {
		vep->dogzip = 1;

		VSB_printf(vep->vsb, "%c", VEC_GZ);
		vep->cb = cb;
	} else {
		vep->cb = vep_default_cb;
	}

	vep->state = VEP_START;
	vep->crc = crc32(0L, Z_NULL, 0);
	vep->crcp = crc32(0L, Z_NULL, 0);


	vep->startup = 1;
	vep->ver_p = "";
	vep->last_mark = SKIP;
	vep_mark_common(vep, vep->ver_p, VERBATIM);
	vep->startup = 0;
}
