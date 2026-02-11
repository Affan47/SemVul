vxge_hw_device_clear_tx_rx(struct __vxge_hw_device *hldev)
{

	if ((hldev->tim_int_mask0[VXGE_HW_VPATH_INTR_TX] != 0) ||
	   (hldev->tim_int_mask0[VXGE_HW_VPATH_INTR_RX] != 0)) {
		writeq((hldev->tim_int_mask0[VXGE_HW_VPATH_INTR_TX] |
				 hldev->tim_int_mask0[VXGE_HW_VPATH_INTR_RX]),
				&hldev->common_reg->tim_int_status0);
	}

	if ((hldev->tim_int_mask1[VXGE_HW_VPATH_INTR_TX] != 0) ||
	   (hldev->tim_int_mask1[VXGE_HW_VPATH_INTR_RX] != 0)) {
		__vxge_hw_pio_mem_write32_upper(
				(hldev->tim_int_mask1[VXGE_HW_VPATH_INTR_TX] |
				 hldev->tim_int_mask1[VXGE_HW_VPATH_INTR_RX]),
				&hldev->common_reg->tim_int_status1);
	}
}
