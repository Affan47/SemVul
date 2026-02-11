efichar_strcmp(const efi_char16_t *s1, const efi_char16_t *s2)
{
	int i;
	int s1_len = efichar_strlen(s1, -1);
	int s2_len = efichar_strlen(s2, -1);


	for (i=0; i < s1_len && i < s2_len; i++) {
		if (s1[i] < s2[i]) return -1;
		if (s1[i] > s2[i]) return 1;

	}

	if (i == s1_len && i != s2_len) return -1;
	if (i != s1_len && i == s2_len) return  1;
	return 0;
}
