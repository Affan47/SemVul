sh_mobile_ceu_stop_streaming(struct vb2_queue *q)
{
	struct soc_camera_device *icd = container_of(q, struct soc_camera_device, vb2_vidq);
	struct soc_camera_host *ici = to_soc_camera_host(icd->parent);
	struct sh_mobile_ceu_dev *pcdev = ici->priv;
	struct list_head *buf_head, *tmp;

	spin_lock_irq(&pcdev->lock);

	pcdev->active = NULL;

	list_for_each_safe(buf_head, tmp, &pcdev->capture)
		list_del_init(buf_head);

	spin_unlock_irq(&pcdev->lock);

	sh_mobile_ceu_soft_reset(pcdev);
}
