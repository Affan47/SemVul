mei_amthif_release(struct mei_device *dev, struct file *file)
{
	if (dev->iamthif_open_count > 0)
		dev->iamthif_open_count--;

	if (dev->iamthif_file_object == file &&
	    dev->iamthif_state != MEI_IAMTHIF_IDLE) {

		dev_dbg(dev->dev, "amthif canceled iamthif state %d\n",
		    dev->iamthif_state);
		dev->iamthif_canceled = true;
		if (dev->iamthif_state == MEI_IAMTHIF_READ_COMPLETE) {
			dev_dbg(dev->dev, "run next amthif iamthif cb\n");
			mei_amthif_run_next_cmd(dev);
		}
	}

	if (mei_clear_lists(dev, file))
		dev->iamthif_state = MEI_IAMTHIF_IDLE;

	return 0;
}
