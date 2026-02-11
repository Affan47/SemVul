bstr_read_ipv4_addr(bstr_t *bs, host_addr_t *ha)
{
	static const char where[] = "bstr_read_ipv4_addr";

	bstr_check(bs);
	g_assert(ha);

	if (!expect(bs, 4, where))
		return FALSE;

	*ha = host_addr_peek_ipv4(bs->rptr);
	bs->rptr += 4;

	return TRUE;
}
