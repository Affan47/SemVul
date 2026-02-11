display_in_hexadecimal (gchar *string, const gchar *data, const gchar *tag)
{
	if ((data == NULL) || (*tag == DMA_DATA_UNDEFINED))
	{
		memcpy(string, "?? ", 3);
	}
	else
	{
		g_sprintf (string, "%02X ", ((unsigned)*data) & 0xFFU);
	}

	return string + 3;
}
