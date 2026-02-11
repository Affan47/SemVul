digest_val_to_str(unsigned int val, char *str)
{
	int err = 0;

	if (val & DIGEST_CRC32C)
		strcpy(str, "CRC32C");
	else if (val & DIGEST_NONE)
		strcpy(str, "None");
	else
		err = -EINVAL;

	return err;
}
