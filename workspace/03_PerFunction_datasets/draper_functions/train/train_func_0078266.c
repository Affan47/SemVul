aa_perm_mask_to_str(char *str, const char *chrs, u32 mask)
{
	unsigned int i, perm = 1;
	for (i = 0; i < 32; perm <<= 1, i++) {
		if (mask & perm)
			*str++ = chrs[i];
	}
	*str = '\0';
}
