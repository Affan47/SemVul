st_nci_i2c_read(struct st_nci_i2c_phy *phy,
				 struct sk_buff **skb)
{
	int r;
	u8 len;
	u8 buf[ST_NCI_I2C_MAX_SIZE];
	struct i2c_client *client = phy->i2c_dev;

	r = i2c_master_recv(client, buf, ST_NCI_I2C_MIN_SIZE);
	if (r < 0) {
		usleep_range(1000, 4000);
		r = i2c_master_recv(client, buf, ST_NCI_I2C_MIN_SIZE);
	}

	if (r != ST_NCI_I2C_MIN_SIZE)
		return -EREMOTEIO;

	len = be16_to_cpu(*(__be16 *) (buf + 2));
	if (len > ST_NCI_I2C_MAX_SIZE) {
		nfc_err(&client->dev, "invalid frame len\n");
		return -EBADMSG;
	}

	*skb = alloc_skb(ST_NCI_I2C_MIN_SIZE + len, GFP_KERNEL);
	if (*skb == NULL)
		return -ENOMEM;

	skb_reserve(*skb, ST_NCI_I2C_MIN_SIZE);
	skb_put(*skb, ST_NCI_I2C_MIN_SIZE);
	memcpy((*skb)->data, buf, ST_NCI_I2C_MIN_SIZE);

	if (!len)
		return 0;

	r = i2c_master_recv(client, buf, len);
	if (r != len) {
		kfree_skb(*skb);
		return -EREMOTEIO;
	}

	skb_put(*skb, len);
	memcpy((*skb)->data + ST_NCI_I2C_MIN_SIZE, buf, len);

	return 0;
}
