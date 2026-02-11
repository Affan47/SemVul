isl12057_can_wakeup_machine(struct device *dev)
{
	struct isl12057_rtc_data *data = dev_get_drvdata(dev);

	return data->irq || of_property_read_bool(dev->of_node, "wakeup-source")
		|| of_property_read_bool(dev->of_node,
					 "isil,irq2-can-wakeup-machine");
}
