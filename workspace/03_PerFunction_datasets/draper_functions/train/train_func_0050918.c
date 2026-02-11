s3fwrn5_nci_send(struct nci_dev *ndev, struct sk_buff *skb)
{
	struct s3fwrn5_info *info = nci_get_drvdata(ndev);
	int ret;

	mutex_lock(&info->mutex);

	if (s3fwrn5_get_mode(info) != S3FWRN5_MODE_NCI) {
		mutex_unlock(&info->mutex);
		return -EINVAL;
	}

	ret = s3fwrn5_write(info, skb);
	if (ret < 0)
		kfree_skb(skb);

	mutex_unlock(&info->mutex);
	return ret;
}
