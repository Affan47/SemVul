vcc_Parse(struct vcc *tl)
{
	struct toplev *tp;

	while (tl->t->tok != EOI) {
		ERRCHK(tl);
		switch (tl->t->tok) {
		case CSRC:
			Fc(tl, 0, "%.*s\n",
			    tl->t->e - (tl->t->b + 4), tl->t->b + 2);
			vcc_NextToken(tl);
			break;
		case EOI:
			break;
		case ID:
			for (tp = toplev; tp->name != NULL; tp++) {
				if (!vcc_IdIs(tl->t, tp->name))
					continue;
				tp->func(tl);
				break;
			}
			if (tp->name != NULL)
				break;

		default:

			VSB_printf(tl->sb, "Expected one of\n\t");
			for (tp = toplev; tp->name != NULL; tp++) {
				if (tp[1].name == NULL)
					VSB_printf(tl->sb, " or ");
				VSB_printf(tl->sb, "'%s'", tp->name);
				if (tp[1].name != NULL)
					VSB_printf(tl->sb, ", ");
			}
			VSB_printf(tl->sb, "\nFound: ");
			vcc_ErrToken(tl, tl->t);
			VSB_printf(tl->sb, " at\n");
			vcc_ErrWhere(tl, tl->t);
			return;
		}
	}
}
