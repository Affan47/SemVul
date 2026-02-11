sil24_tag(int tag)
{
	if (unlikely(ata_tag_internal(tag)))
		return 0;
	return tag;
}
