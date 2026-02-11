async_load_cb(struct libusb_transfer *transfer)
{
	struct fpi_ssm *ssm = transfer->user_data;
	struct fp_img_dev *dev = ssm->priv;
	struct vfs101_dev *vdev = dev->priv;


	vdev->transfer = NULL;


	if (!vdev->ignore_error)
	{
		if (transfer->status != LIBUSB_TRANSFER_COMPLETED)
		{

			fp_err("transfer not completed, status = %d, length = %d", transfer->status, vdev->length);
			fpi_imgdev_session_error(dev, -EIO);
			fpi_ssm_mark_aborted(ssm, -EIO);
			goto out;
		}

		if (transfer->actual_length % VFS_FRAME_SIZE)
		{

			fp_err("received incomplete frame");
			fpi_imgdev_session_error(dev, -EIO);
			fpi_ssm_mark_aborted(ssm, -EIO);
			goto out;
		}
	}


	vdev->length += transfer->actual_length;

	if (transfer->actual_length == VFS_BLOCK_SIZE)
	{
		if ((VFS_BUFFER_SIZE - vdev->length) < VFS_BLOCK_SIZE)
		{

			fp_err("buffer full, image too large");
			fpi_imgdev_session_error(dev, -ENOMEM);
			fpi_ssm_mark_aborted(ssm, -ENOMEM);
			goto out;
		}
		else

			async_load(ssm);
	}
	else
	{

		if (vdev->ignore_error)
			vdev->ignore_error = FALSE;


		vdev->height = vdev->length / VFS_FRAME_SIZE;
		fp_dbg("image loaded, height = %d", vdev->height);
		fpi_ssm_next_state(ssm);
	}

out:
	libusb_free_transfer(transfer);
}
