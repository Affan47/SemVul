ath10k_wmi_event_debug_print(struct ath10k *ar, struct sk_buff *skb)
{
	char buf[101], c;
	int i;

	for (i = 0; i < sizeof(buf) - 1; i++) {
		if (i >= skb->len)
			break;

		c = skb->data[i];

		if (c == '\0')
			break;

		if (isascii(c) && isprint(c))
			buf[i] = c;
		else
			buf[i] = '.';
	}

	if (i == sizeof(buf) - 1)
		ath10k_warn(ar, "wmi debug print truncated: %d\n", skb->len);


	if (skb->data[i - 1] == '\n')
		i--;


	buf[i] = '\0';

	ath10k_dbg(ar, ATH10K_DBG_WMI_PRINT, "wmi print '%s'\n", buf);
}
