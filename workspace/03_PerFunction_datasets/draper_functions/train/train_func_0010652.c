cyttsp_close(struct input_dev *dev)
{
	struct cyttsp *ts = input_get_drvdata(dev);

	if (!ts->suspended)
		cyttsp_disable(ts);
}
