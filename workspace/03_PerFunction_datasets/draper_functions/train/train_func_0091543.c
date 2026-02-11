dln2_gpio_get_pin_count(struct platform_device *pdev)
{
	int ret;
	__le16 count;
	int len = sizeof(count);

	ret = dln2_transfer_rx(pdev, DLN2_GPIO_GET_PIN_COUNT, &count, &len);
	if (ret < 0)
		return ret;
	if (len < sizeof(count))
		return -EPROTO;

	return le16_to_cpu(count);
}
