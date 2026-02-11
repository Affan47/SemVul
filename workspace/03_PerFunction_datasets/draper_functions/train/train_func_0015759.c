jfs_strfromUCS_le(char *to, const __le16 * from,
		      int len, struct nls_table *codepage)
{
	int i;
	int outlen = 0;
	static int warn_again = 5;
	int warn = !!warn_again;

	if (codepage) {
		for (i = 0; (i < len) && from[i]; i++) {
			int charlen;
			charlen =
			    codepage->uni2char(le16_to_cpu(from[i]),
					       &to[outlen],
					       NLS_MAX_CHARSET_SIZE);
			if (charlen > 0)
				outlen += charlen;
			else
				to[outlen++] = '?';
		}
	} else {
		for (i = 0; (i < len) && from[i]; i++) {
			if (unlikely(le16_to_cpu(from[i]) & 0xff00)) {
				to[i] = '?';
				if (unlikely(warn)) {
					warn--;
					warn_again--;
					printk(KERN_ERR
			"non-latin1 character 0x%x found in JFS file name\n",
					       le16_to_cpu(from[i]));
					printk(KERN_ERR
				"mount with iocharset=utf8 to access\n");
				}

			}
			else
				to[i] = (char) (le16_to_cpu(from[i]));
		}
		outlen = i;
	}
	to[outlen] = 0;
	return outlen;
}
