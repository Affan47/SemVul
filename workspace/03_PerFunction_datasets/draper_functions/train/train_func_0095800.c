compute_atomic_domain(
	struct isl_codegen_domains *domains, __isl_take isl_set *class_domain)
{
	isl_basic_set *bset;
	isl_basic_set_list *list;
	isl_set *domain, *atomic_domain;
	int empty;

	domain = isl_set_copy(domains->option[isl_ast_loop_atomic]);
	domain = isl_set_intersect(domain, isl_set_copy(class_domain));
	domain = isl_set_intersect(domain,
				isl_set_copy(domains->schedule_domain));
	empty = isl_set_is_empty(domain);
	if (empty < 0)
		class_domain = isl_set_free(class_domain);
	if (empty) {
		isl_set_free(domain);
		return class_domain;
	}

	domain = isl_ast_build_eliminate(domains->build, domain);
	domain = isl_set_coalesce(domain);
	bset = isl_set_unshifted_simple_hull(domain);
	domain = isl_set_from_basic_set(bset);
	atomic_domain = isl_set_copy(domain);
	domain = isl_set_intersect(domain, isl_set_copy(class_domain));
	class_domain = isl_set_subtract(class_domain, atomic_domain);
	domain = isl_set_make_disjoint(domain);
	list = isl_basic_set_list_from_set(domain);
	domains->list = isl_basic_set_list_concat(domains->list, list);

	return class_domain;
}
