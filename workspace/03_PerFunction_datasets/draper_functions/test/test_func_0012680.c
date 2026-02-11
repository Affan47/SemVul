show_available_governors(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	ssize_t i = 0;
	struct cpuidle_governor *tmp;

	mutex_lock(&cpuidle_lock);
	list_for_each_entry(tmp, &cpuidle_governors, governor_list) {
		if (i >= (ssize_t) ((PAGE_SIZE/sizeof(char)) -
				    CPUIDLE_NAME_LEN - 2))
			goto out;
		i += scnprintf(&buf[i], CPUIDLE_NAME_LEN, "%s ", tmp->name);
	}

out:
	i+= sprintf(&buf[i], "\n");
	mutex_unlock(&cpuidle_lock);
	return i;
}
