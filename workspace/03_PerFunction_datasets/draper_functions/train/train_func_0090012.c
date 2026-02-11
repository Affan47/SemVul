update_delta_is_binary(git_diff_delta *delta)
{
	if ((delta->old_file.flags & GIT_DIFF_FLAG_BINARY) != 0 ||
		(delta->new_file.flags & GIT_DIFF_FLAG_BINARY) != 0)
		delta->flags |= GIT_DIFF_FLAG_BINARY;

	else if ((delta->old_file.flags & NOT_BINARY_FLAGS) != 0 &&
			 (delta->new_file.flags & NOT_BINARY_FLAGS) != 0)
		delta->flags |= GIT_DIFF_FLAG_NOT_BINARY;


}
