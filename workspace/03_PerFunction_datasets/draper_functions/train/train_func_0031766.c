max17042_suspend(struct device *dev)
{
	struct max17042_chip *chip = dev_get_drvdata(dev);


	if (chip->client->irq) {
		disable_irq(chip->client->irq);
		enable_irq_wake(chip->client->irq);
	}

	return 0;
}
