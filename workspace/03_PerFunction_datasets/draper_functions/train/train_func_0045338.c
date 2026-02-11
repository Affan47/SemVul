ssp_irq_msg(struct ssp_data *data)
{
	bool found = false;
	char *buffer;
	u8 msg_type;
	int ret;
	u16 length, msg_options;
	struct ssp_msg *msg, *n;

	ret = spi_read(data->spi, data->header_buffer, SSP_HEADER_BUFFER_SIZE);
	if (ret < 0) {
		dev_err(SSP_DEV, "header read fail\n");
		return ret;
	}

	length = le16_to_cpu(data->header_buffer[1]);
	msg_options = le16_to_cpu(data->header_buffer[0]);

	if (length == 0) {
		dev_err(SSP_DEV, "length received from mcu is 0\n");
		return -EINVAL;
	}

	msg_type = SSP_GET_MESSAGE_TYPE(msg_options);

	switch (msg_type) {
	case SSP_AP2HUB_READ:
	case SSP_AP2HUB_WRITE:


		mutex_lock(&data->pending_lock);
		list_for_each_entry_safe(msg, n, &data->pending_list, list) {
			if (msg->options == msg_options) {
				list_del(&msg->list);
				found = true;
				break;
			}
		}

		if (!found) {


			buffer = kmalloc(length, GFP_KERNEL | GFP_DMA);
			if (!buffer) {
				ret = -ENOMEM;
				goto _unlock;
			}


			ret = spi_read(data->spi, buffer, length);
			if (ret >= 0)
				ret = -EPROTO;

			kfree(buffer);

			dev_err(SSP_DEV, "No match error %x\n",
				msg_options);

			goto _unlock;
		}

		if (msg_type == SSP_AP2HUB_READ)
			ret = spi_read(data->spi,
				       &msg->buffer[SSP_HEADER_SIZE_ALIGNED],
				       msg->length);

		if (msg_type == SSP_AP2HUB_WRITE) {
			ret = spi_write(data->spi,
					&msg->buffer[SSP_HEADER_SIZE_ALIGNED],
					msg->length);
			if (msg_options & SSP_AP2HUB_RETURN) {
				msg->options =
					SSP_AP2HUB_READ | SSP_AP2HUB_RETURN;
				msg->length = 1;

				list_add_tail(&msg->list, &data->pending_list);
				goto _unlock;
			}
		}

		if (msg->done)
			if (!completion_done(msg->done))
				complete(msg->done);
_unlock:
		mutex_unlock(&data->pending_lock);
		break;
	case SSP_HUB2AP_WRITE:
		buffer = kzalloc(length, GFP_KERNEL | GFP_DMA);
		if (!buffer)
			return -ENOMEM;

		ret = spi_read(data->spi, buffer, length);
		if (ret < 0) {
			dev_err(SSP_DEV, "spi read fail\n");
			kfree(buffer);
			break;
		}

		ret = ssp_parse_dataframe(data, buffer, length);

		kfree(buffer);
		break;

	default:
		dev_err(SSP_DEV, "unknown msg type\n");
		return -EPROTO;
	}

	return ret;
}
