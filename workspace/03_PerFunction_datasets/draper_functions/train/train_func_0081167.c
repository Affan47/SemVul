_get_job_features(struct job_record *job_ptr)
{
	int i;
	char *rfeatures;

	if ((job_ptr->details == NULL)
	||  (job_ptr->details->features == NULL)
	||  (job_ptr->details->features[0] == '\0'))
		return NULL;

	rfeatures = xstrdup(job_ptr->details->features);

	for (i=0; ; i++) {
		if (rfeatures[i] == '\0')
			return rfeatures;
		if (rfeatures[i] == '|')
			break;
		if (rfeatures[i] == '&')
			rfeatures[i] = ':';
	}


	xfree(rfeatures);
	return NULL;
}
