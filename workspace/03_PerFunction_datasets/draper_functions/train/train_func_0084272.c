bstr_read_u8(bstr_t *bs, uint8 *pv)
{
	bstr_check(bs);
	g_assert(pv);

	if (!expect(bs, 1, "bstr_read_u8"))
		return FALSE;

	*pv = peek_u8(bs->rptr++);
	return TRUE;
}
