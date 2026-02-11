dev_pm_qos_add_ancestor_request(struct device *dev,
				    struct dev_pm_qos_request *req,
				    enum dev_pm_qos_req_type type, s32 value)
{
	struct device *ancestor = dev->parent;
	int ret = -ENODEV;

	switch (type) {
	case DEV_PM_QOS_RESUME_LATENCY:
		while (ancestor && !ancestor->power.ignore_children)
			ancestor = ancestor->parent;

		break;
	case DEV_PM_QOS_LATENCY_TOLERANCE:
		while (ancestor && !ancestor->power.set_latency_tolerance)
			ancestor = ancestor->parent;

		break;
	default:
		ancestor = NULL;
	}
	if (ancestor)
		ret = dev_pm_qos_add_request(ancestor, req, type, value);

	if (ret < 0)
		req->dev = NULL;

	return ret;
}
