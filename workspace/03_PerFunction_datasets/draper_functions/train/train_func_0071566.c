ALL_GetNodeType(const u32 *table, const u32 count, u32 NodeTag, u32 Version)
{
	u32 i = 0;
	while (i<count) {
		if (table[i] == NodeTag) goto found;
		i++;
	}
	return 0;
found:
	if (Version == 2) return i+2;
	return i+1;
}
