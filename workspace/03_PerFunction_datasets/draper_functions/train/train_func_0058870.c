soc_camera_prepare_buf(struct file *file, void *priv,
				  struct v4l2_buffer *b)
{
	struct soc_camera_device *icd = file->private_data;
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);


	if (ici->ops->init_videobuf)
		return -EINVAL;
	else
		return vb2_prepare_buf(&icd->vb2_vidq, b);
}
