adpt_open(struct inode *inode, struct file *file)
{
	int minor;
	adpt_hba* pHba;

	mutex_lock(&adpt_mutex);


	minor = iminor(inode);
	if (minor >= hba_count) {
		mutex_unlock(&adpt_mutex);
		return -ENXIO;
	}
	mutex_lock(&adpt_configuration_lock);
	for (pHba = hba_chain; pHba; pHba = pHba->next) {
		if (pHba->unit == minor) {
			break;
		}
	}
	if (pHba == NULL) {
		mutex_unlock(&adpt_configuration_lock);
		mutex_unlock(&adpt_mutex);
		return -ENXIO;
	}


	pHba->in_use = 1;
	mutex_unlock(&adpt_configuration_lock);
	mutex_unlock(&adpt_mutex);

	return 0;
}
