dev_pm_opp_remove(struct device *dev, unsigned long freq)
{
	struct dev_pm_opp *opp;
	struct device_opp *dev_opp;
	bool found = false;


	mutex_lock(&dev_opp_list_lock);

	dev_opp = _find_device_opp(dev);
	if (IS_ERR(dev_opp))
		goto unlock;

	list_for_each_entry(opp, &dev_opp->opp_list, node) {
		if (opp->rate == freq) {
			found = true;
			break;
		}
	}

	if (!found) {
		dev_warn(dev, "%s: Couldn't find OPP with freq: %lu\n",
			 __func__, freq);
		goto unlock;
	}

	_opp_remove(dev_opp, opp, true);
unlock:
	mutex_unlock(&dev_opp_list_lock);
}
