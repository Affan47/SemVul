htcpld_unregister_chip_i2c(
		struct platform_device *pdev,
		int chip_index)
{
	struct htcpld_data *htcpld;
	struct htcpld_chip *chip;


	htcpld = platform_get_drvdata(pdev);
	chip = &htcpld->chip[chip_index];

	if (chip->client)
		i2c_unregister_device(chip->client);
}
