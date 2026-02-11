cyttsp_resume(struct device *dev)
{
	struct cyttsp *ts = dev_get_drvdata(dev);

	mutex_lock(&ts->input->mutex);

	if (ts->input->users)
		cyttsp_enable(ts);

	ts->suspended = false;

	mutex_unlock(&ts->input->mutex);

	return 0;
}
