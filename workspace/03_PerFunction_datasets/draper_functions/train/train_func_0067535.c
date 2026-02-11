report_path_error(const char *ps_matched, const char **pathspec, int prefix_offset)
{


	int num, errors = 0;
	for (num = 0; pathspec[num]; num++) {
		int other, found_dup;

		if (ps_matched[num])
			continue;


		for (found_dup = other = 0;
		     !found_dup && pathspec[other];
		     other++) {
			if (other == num || !ps_matched[other])
				continue;
			if (!strcmp(pathspec[other], pathspec[num]))


				found_dup = 1;
		}
		if (found_dup)
			continue;

		error("pathspec '%s' did not match any file(s) known to git.",
		      pathspec[num] + prefix_offset);
		errors++;
	}
	return errors;
}
