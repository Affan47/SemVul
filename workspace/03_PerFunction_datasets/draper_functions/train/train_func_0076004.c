handle_delete_modify(struct merge_options *o,
				 const char *path,
				 const char *new_path,
				 unsigned char *a_sha, int a_mode,
				 unsigned char *b_sha, int b_mode)
{
	if (!a_sha) {
		output(o, 1, "CONFLICT (delete/modify): %s deleted in %s "
		       "and modified in %s. Version %s of %s left in tree%s%s.",
		       path, o->branch1,
		       o->branch2, o->branch2, path,
		       path == new_path ? "" : " at ",
		       path == new_path ? "" : new_path);
		update_file(o, 0, b_sha, b_mode, new_path);
	} else {
		output(o, 1, "CONFLICT (delete/modify): %s deleted in %s "
		       "and modified in %s. Version %s of %s left in tree%s%s.",
		       path, o->branch2,
		       o->branch1, o->branch1, path,
		       path == new_path ? "" : " at ",
		       path == new_path ? "" : new_path);
		update_file(o, 0, a_sha, a_mode, new_path);
	}
}
