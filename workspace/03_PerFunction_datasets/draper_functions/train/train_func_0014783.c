mbox_request_channel(struct mbox_client *cl, int index)
{
	struct device *dev = cl->dev;
	struct mbox_controller *mbox;
	struct of_phandle_args spec;
	struct mbox_chan *chan;
	unsigned long flags;
	int ret;

	if (!dev || !dev->of_node) {
		pr_debug("%s: No owner device node\n", __func__);
		return ERR_PTR(-ENODEV);
	}

	mutex_lock(&con_mutex);

	if (of_parse_phandle_with_args(dev->of_node, "mboxes",
				       "#mbox-cells", index, &spec)) {
		dev_dbg(dev, "%s: can't parse \"mboxes\" property\n", __func__);
		mutex_unlock(&con_mutex);
		return ERR_PTR(-ENODEV);
	}

	chan = ERR_PTR(-EPROBE_DEFER);
	list_for_each_entry(mbox, &mbox_cons, node)
		if (mbox->dev->of_node == spec.np) {
			chan = mbox->of_xlate(mbox, &spec);
			break;
		}

	of_node_put(spec.np);

	if (IS_ERR(chan)) {
		mutex_unlock(&con_mutex);
		return chan;
	}

	if (chan->cl || !try_module_get(mbox->dev->driver->owner)) {
		dev_dbg(dev, "%s: mailbox not free\n", __func__);
		mutex_unlock(&con_mutex);
		return ERR_PTR(-EBUSY);
	}

	spin_lock_irqsave(&chan->lock, flags);
	chan->msg_free = 0;
	chan->msg_count = 0;
	chan->active_req = NULL;
	chan->cl = cl;
	init_completion(&chan->tx_complete);

	if (chan->txdone_method	== TXDONE_BY_POLL && cl->knows_txdone)
		chan->txdone_method |= TXDONE_BY_ACK;

	spin_unlock_irqrestore(&chan->lock, flags);

	ret = chan->mbox->ops->startup(chan);
	if (ret) {
		dev_err(dev, "Unable to startup the chan (%d)\n", ret);
		mbox_free_channel(chan);
		chan = ERR_PTR(ret);
	}

	mutex_unlock(&con_mutex);
	return chan;
}
