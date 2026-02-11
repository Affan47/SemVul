link_alt_odb_entries(const char *alt, const char *ep, int sep,
				 const char *relative_base, int depth)
{
	const char *cp, *last;

	if (depth > 5) {
		error("%s: ignoring alternate object stores, nesting too deep.",
				relative_base);
		return;
	}

	last = alt;
	while (last < ep) {
		cp = last;
		if (cp < ep && *cp == '#') {
			while (cp < ep && *cp != sep)
				cp++;
			last = cp + 1;
			continue;
		}
		while (cp < ep && *cp != sep)
			cp++;
		if (last != cp) {
			if ((*last != '/') && depth) {
				error("%s: ignoring relative alternate object store %s",
						relative_base, last);
			} else {
				link_alt_odb_entry(last, cp - last,
						relative_base, depth);
			}
		}
		while (cp < ep && *cp == sep)
			cp++;
		last = cp;
	}
}
