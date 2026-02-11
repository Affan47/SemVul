acl_cond_kw_conflicts(const struct acl_cond *cond, unsigned int where, struct acl const **acl, char const **kw)
{
	struct acl_term_suite *suite;
	struct acl_term *term;
	struct acl_expr *expr;

	list_for_each_entry(suite, &cond->suites, list) {
		list_for_each_entry(term, &suite->terms, list) {
			list_for_each_entry(expr, &term->acl->expr, list) {
				if (!(expr->smp->fetch->val & where)) {
					if (acl)
						*acl = term->acl;
					if (kw)
						*kw = expr->kw;
					return 1;
				}
			}
		}
	}
	return 0;
}
