show_temp(struct device *dev,
			struct device_attribute *devattr, char *buf)
{
	u32 eax, edx;
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	struct platform_data *pdata = dev_get_drvdata(dev);
	struct temp_data *tdata = pdata->core_data[attr->index];

	mutex_lock(&tdata->update_lock);


	if (!tdata->valid || time_after(jiffies, tdata->last_updated + HZ)) {
		rdmsr_on_cpu(tdata->cpu, tdata->status_reg, &eax, &edx);


		tdata->temp = tdata->tjmax - ((eax >> 16) & 0x7f) * 1000;
		tdata->valid = 1;
		tdata->last_updated = jiffies;
	}

	mutex_unlock(&tdata->update_lock);
	return sprintf(buf, "%d\n", tdata->temp);
}
