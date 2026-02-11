journal_tag_bytes(journal_t *journal)
{
	size_t sz;

	if (jbd2_has_feature_csum3(journal))
		return sizeof(journal_block_tag3_t);

	sz = sizeof(journal_block_tag_t);

	if (jbd2_has_feature_csum2(journal))
		sz += sizeof(__u16);

	if (jbd2_has_feature_64bit(journal))
		return sz;
	else
		return sz - sizeof(__u32);
}
