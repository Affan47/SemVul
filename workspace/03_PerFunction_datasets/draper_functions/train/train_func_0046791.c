br_strcat (const char *str1, const char *str2)
{
	char *result;
	size_t len1, len2;

	if (!str1) str1 = "";
	if (!str2) str2 = "";

	len1 = strlen (str1);
	len2 = strlen (str2);

	result = (char *) malloc (len1 + len2 + 1);
	memcpy (result, str1, len1);
	memcpy (result + len1, str2, len2);
	result[len1 + len2] = '\0';

	return result;
}
