unlink_class(struct class **class) {
	struct collection *lp;
	struct class *cp, *pp;

	for (lp = collections; lp; lp = lp -> next) {
		for (pp = 0, cp = lp -> classes; cp; pp = cp, cp = cp -> nic)
			if (cp == *class) {
				if (pp == 0) {
					lp->classes = cp->nic;
				} else {
					pp->nic = cp->nic;
				}
				cp->nic = 0;
				class_dereference(class, MDL);

				return ISC_R_SUCCESS;
			}
	}
	return ISC_R_NOTFOUND;
}
