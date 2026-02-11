amd_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	struct amd_gpio *agp = to_agp(chip);

	dev_dbg(&agp->pdev->dev, "Freed gpio %d, data %x\n", offset, agp->orig[offset]);

	iowrite8(agp->orig[offset], agp->pm + AMD_REG_GPIO(offset));
}
