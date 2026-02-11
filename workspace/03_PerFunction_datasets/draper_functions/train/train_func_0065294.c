pinctrl_find_gpio_range_from_pin(struct pinctrl_dev *pctldev,
				 unsigned int pin)
{
	struct pinctrl_gpio_range *range;

	mutex_lock(&pctldev->mutex);

	list_for_each_entry(range, &pctldev->gpio_ranges, node) {

		if (range->pins) {
			int a;
			for (a = 0; a < range->npins; a++) {
				if (range->pins[a] == pin)
					goto out;
			}
		} else if (pin >= range->pin_base &&
			   pin < range->pin_base + range->npins)
			goto out;
	}
	range = NULL;
out:
	mutex_unlock(&pctldev->mutex);
	return range;
}
