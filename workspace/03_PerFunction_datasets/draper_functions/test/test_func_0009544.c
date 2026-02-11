batch_result_list_append_list(batch_result_list_ty *p,
    const batch_result_list_ty *p2)
{
    for (size_t j = 0; j < p2->length; ++j)
    {
	const batch_result_ty *brp2 = p2->item + j;
	batch_result_list_append
	(
	    p,
	    brp2->file_name,
	    brp2->exit_status,
	    brp2->architecture,
            brp2->elapsed
	);
    }
    p->pass_count += p2->pass_count;
    p->skip_count += p2->skip_count;
    p->no_result_count += p2->no_result_count;
    p->fail_count += p2->fail_count;
    p->elapsed += p2->elapsed;
}
