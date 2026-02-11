virtscsi_remove(struct virtio_device *vdev)
{
	struct Scsi_Host *shost = virtio_scsi_host(vdev);
	struct virtio_scsi *vscsi = shost_priv(shost);

	if (virtio_has_feature(vdev, VIRTIO_SCSI_F_HOTPLUG))
		virtscsi_cancel_event_work(vscsi);

	scsi_remove_host(shost);

	unregister_hotcpu_notifier(&vscsi->nb);

	virtscsi_remove_vqs(vdev);
	scsi_host_put(shost);
}
