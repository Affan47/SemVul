read_hrecs (List *flist)
{
    int files_read;


    hrec_max = HREC_INCREMENT;
    hrec_head = xmalloc (hrec_max * sizeof (struct hrec));
    hrec_idx = 0;

    files_read = walklist (flist, read_hrecs_file, NULL);
    if (!files_read)
	error (1, 0, "No history files read.");


    if (last_since_tag)
    {
	hrec_count -= (last_since_tag - hrec_head);
	hrec_head = last_since_tag;
    }


    if (last_backto)
    {
	hrec_count -= (last_backto - hrec_head);
	hrec_head = last_backto;
    }
}
