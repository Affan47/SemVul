ck_is_readonly(ckhunk_t *ck)
{
	ckhunk_check(ck);

	return NULL == ck ? FALSE : ck->read_only;
}
