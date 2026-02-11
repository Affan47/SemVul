n_elt(struct Dimblock *vd)
#endif
{
	expptr ne;
	long nv = 1;
	if (vd) {
		if (!(ne = vd->nelt))
			Fatal("Null nelt in n_elt");
		if (ne->tag != TCONST)
			fatali("Unexpected nelt tag %d in n_elt", ne->tag);
		if (!ISINT(ne->constblock.vtype))
			fatali("Unexpected vtype %d in n_elt",
				ne->constblock.vtype);
		nv = ne->constblock.Const.ci;
		}
	return nv;
	}
