ECPoint_mul(const ECGroup *group, const mp_int *k, const mp_int *px,
			const mp_int *py, mp_int *rx, mp_int *ry)
{
	mp_err res = MP_OKAY;
	mp_int kt;

	ARGCHK((k != NULL) && (group != NULL), MP_BADARG);
	MP_DIGITS(&kt) = 0;


	if (mp_cmp(k, &group->order) > 0) {
		MP_CHECKOK(mp_init(&kt));
		MP_CHECKOK(mp_mod(k, &group->order, &kt));
	} else {
		MP_SIGN(&kt) = MP_ZPOS;
		MP_USED(&kt) = MP_USED(k);
		MP_ALLOC(&kt) = MP_ALLOC(k);
		MP_DIGITS(&kt) = MP_DIGITS(k);
	}

	if ((px == NULL) || (py == NULL)) {
		if (group->base_point_mul) {
			MP_CHECKOK(group->base_point_mul(&kt, rx, ry, group));
		} else {
			MP_CHECKOK(group->
					   point_mul(&kt, &group->genx, &group->geny, rx, ry,
								 group));
		}
	} else {
		if (group->meth->field_enc) {
			MP_CHECKOK(group->meth->field_enc(px, rx, group->meth));
			MP_CHECKOK(group->meth->field_enc(py, ry, group->meth));
			MP_CHECKOK(group->point_mul(&kt, rx, ry, rx, ry, group));
		} else {
			MP_CHECKOK(group->point_mul(&kt, px, py, rx, ry, group));
		}
	}
	if (group->meth->field_dec) {
		MP_CHECKOK(group->meth->field_dec(rx, rx, group->meth));
		MP_CHECKOK(group->meth->field_dec(ry, ry, group->meth));
	}

  CLEANUP:
	if (MP_DIGITS(&kt) != MP_DIGITS(k)) {
		mp_clear(&kt);
	}
	return res;
}
