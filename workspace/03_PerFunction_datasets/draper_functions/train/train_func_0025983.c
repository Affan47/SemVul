sms_udh_iter_next(struct sms_udh_iter *iter)
{
	if (iter->offset > iter->data[0])
		return FALSE;

	iter->offset = iter->offset + 2 + iter->data[iter->offset + 1];

	if (iter->offset > iter->data[0])
		return FALSE;

	return TRUE;
}
