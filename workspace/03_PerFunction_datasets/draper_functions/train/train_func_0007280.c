VXGE_COMPLETE_ALL_RX(struct vxgedev *vdev)
{
	int i;
	struct vxge_ring *ring;


	for (i = 0; i < vdev->no_of_vpath; i++) {
		ring = &vdev->vpaths[i].ring;
		vxge_hw_vpath_poll_rx(ring->handle);
	}
}
