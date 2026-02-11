ss_variance(cst_ss *ss)
{
    if (ss->num_samples > 1)
	return ((ss->num_samples*ss->sumx)-(ss->sum*ss->sum))/
	    (ss->num_samples*(ss->num_samples-1));
    else
	return 0;
}
