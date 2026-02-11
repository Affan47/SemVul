get_frame_size(const cst_sts_list *sts_list, int frame)
{
    if (sts_list->sts)
	return sts_list->sts[frame].size;
    else if (sts_list->sts_paged)
	return sts_list->sts_paged[frame].res_size;
    else
    {


	return sts_list->resoffs[frame+1] - sts_list->resoffs[frame];
    }
}
