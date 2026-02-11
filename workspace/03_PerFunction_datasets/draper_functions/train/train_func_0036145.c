responsecmp(void *instance UNUSED,
		       REQUEST *req,
		       VALUE_PAIR *request UNUSED,
		       VALUE_PAIR *check,
		       VALUE_PAIR *check_pairs UNUSED,
		       VALUE_PAIR **reply_pairs UNUSED)
{
	if (req->reply->code == check->vp_integer) {
		return 0;
	}

	return 1;
}
