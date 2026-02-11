carl9170_rx(struct ar9170 *ar, void *buf, unsigned int len)
{
	if (ar->fw.rx_stream)
		carl9170_rx_stream(ar, buf, len);
	else
		__carl9170_rx(ar, buf, len);
}
