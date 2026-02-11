head_ref(each_ref_fn fn, void *cb_data)
{
	unsigned char sha1[20];
	int flag;

	if (resolve_ref("HEAD", sha1, 1, &flag))
		return fn("HEAD", sha1, flag, cb_data);
	return 0;
}
