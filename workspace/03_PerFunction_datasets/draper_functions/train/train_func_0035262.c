pn533_rf_complete(struct pn533 *dev, void *arg,
			     struct sk_buff *resp)
{
	int rc = 0;

	dev_dbg(&dev->interface->dev, "%s\n", __func__);

	if (IS_ERR(resp)) {
		rc = PTR_ERR(resp);

		nfc_err(&dev->interface->dev, "RF setting error %d\n", rc);

		return rc;
	}

	queue_delayed_work(dev->wq, &dev->poll_work,
			   msecs_to_jiffies(PN533_POLL_INTERVAL));

	dev_kfree_skb(resp);
	return rc;
}
