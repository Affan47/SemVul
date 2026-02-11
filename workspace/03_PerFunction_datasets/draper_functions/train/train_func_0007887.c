cb_build_assignment_name (struct cb_file *cfile, cb_tree name)
{
	const char	*s;
	const char	*p;

	if (name == cb_error_node) {
		return cb_error_node;
	}

	switch (CB_TREE_TAG (name)) {
	case CB_TAG_LITERAL:
		if (strcmp ((char *)(CB_LITERAL(name)->data), "$#@DUMMY@#$") == 0) {
			cfile->special = 2;
		}
		return name;

	case CB_TAG_REFERENCE:
		s = CB_REFERENCE (name)->word->name;
		if (strcasecmp (s, "KEYBOARD") == 0) {
			s = "#DUMMY#";
			cfile->special = 1;
			return cb_build_alphanumeric_literal ((ucharptr)s, strlen (s));
		}
		switch (cb_assign_clause) {
		case CB_ASSIGN_COBOL2002:

			return cb_error_node;

		case CB_ASSIGN_MF:
			if (cfile->external_assign) {
				p = strrchr (s, '-');
				if (p) {
					s = p + 1;
				}
				return cb_build_alphanumeric_literal ((ucharptr)s, strlen (s));
			}
			current_program->reference_list =
			    cb_list_add (current_program->reference_list, name);
			return name;

		case CB_ASSIGN_IBM:

			if (strncmp (s, "S-", 2) == 0 ||
			    strncmp (s, "AS-", 3) == 0) {
				goto org;
			}

			if ((p = strchr (s, '-')) != NULL) {
				s = p + 1;
			}

			if (strncmp (s, "S-", 2) == 0 ||
			    strncmp (s, "AS-", 3) == 0) {
org:

				s = strchr (s, '-') + 1;
			}

			return cb_build_alphanumeric_literal ((ucharptr)s, strlen (s));
		}

	default:
		return cb_error_node;
	}
}
