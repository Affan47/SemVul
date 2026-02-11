job_option_info_unpack (Buf buf)
{
	struct job_option_info *ji = xmalloc (sizeof (*ji));
	uint32_t type;
	uint32_t len;

	safe_unpack32 (&type, buf);
	safe_unpackstr_xmalloc (&ji->option, &len, buf);
	safe_unpackstr_xmalloc (&ji->optarg, &len, buf);

	ji->type = (int) type;
	return (ji);

  unpack_error:
	job_option_info_destroy (ji);
	return (NULL);
}
