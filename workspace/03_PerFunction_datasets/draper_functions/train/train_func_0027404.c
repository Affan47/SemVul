mod_count_all_dependencies(const struct mod *mod)
{
	size_t i, count = 0;
	for (i = 0; i < mod->deps.count; i++) {
		const struct mod *d = mod->deps.array[i];
		count += 1 + mod_count_all_dependencies(d);
	}
	return count;
}
