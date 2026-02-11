copy_all(void)
{
	struct  spdet	*up, *ue = &ulist[Nusers];
	for  (up = ulist;  up < ue;  up++)  {
		up->spu_minp = Spuhdr.sph_minp;
		up->spu_maxp = Spuhdr.sph_maxp;
		up->spu_defp = Spuhdr.sph_defp;
		up->spu_cps = Spuhdr.sph_cps;
		strcpy(up->spu_form, Spuhdr.sph_form);
		strcpy(up->spu_formallow, Spuhdr.sph_formallow);
		strcpy(up->spu_ptr, Spuhdr.sph_ptr);
		strcpy(up->spu_ptrallow, Spuhdr.sph_ptrallow);
		up->spu_class = Spuhdr.sph_class;
		if  (up->spu_user != Realuid)
			up->spu_flgs = Spuhdr.sph_flgs;
	}
}
