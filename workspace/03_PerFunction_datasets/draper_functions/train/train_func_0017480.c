rev_list_free (rev_list *rl, int free_files)
{
    rev_head_free (rl->heads, free_files);
    if (free_files)
	rev_file_free_marked ();
    free (rl);
}
