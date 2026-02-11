vmci_dispatch_dgs(unsigned long data)
{
	struct vmci_guest_device *vmci_dev = (struct vmci_guest_device *)data;
	u8 *dg_in_buffer = vmci_dev->data_buffer;
	struct vmci_datagram *dg;
	size_t dg_in_buffer_size = VMCI_MAX_DG_SIZE;
	size_t current_dg_in_buffer_size = PAGE_SIZE;
	size_t remaining_bytes;

	BUILD_BUG_ON(VMCI_MAX_DG_SIZE < PAGE_SIZE);

	ioread8_rep(vmci_dev->iobase + VMCI_DATA_IN_ADDR,
		    vmci_dev->data_buffer, current_dg_in_buffer_size);
	dg = (struct vmci_datagram *)dg_in_buffer;
	remaining_bytes = current_dg_in_buffer_size;

	while (dg->dst.resource != VMCI_INVALID_ID ||
	       remaining_bytes > PAGE_SIZE) {
		unsigned dg_in_size;


		if (dg->dst.resource == VMCI_INVALID_ID) {
			dg = (struct vmci_datagram *)roundup(
				(uintptr_t)dg + 1, PAGE_SIZE);
			remaining_bytes =
				(size_t)(dg_in_buffer +
					 current_dg_in_buffer_size -
					 (u8 *)dg);
			continue;
		}

		dg_in_size = VMCI_DG_SIZE_ALIGNED(dg);

		if (dg_in_size <= dg_in_buffer_size) {
			int result;


			if (dg_in_size > remaining_bytes) {
				if (remaining_bytes !=
				    current_dg_in_buffer_size) {


					memmove(dg_in_buffer, dg_in_buffer +
						current_dg_in_buffer_size -
						remaining_bytes,
						remaining_bytes);
					dg = (struct vmci_datagram *)
					    dg_in_buffer;
				}

				if (current_dg_in_buffer_size !=
				    dg_in_buffer_size)
					current_dg_in_buffer_size =
					    dg_in_buffer_size;

				ioread8_rep(vmci_dev->iobase +
						VMCI_DATA_IN_ADDR,
					vmci_dev->data_buffer +
						remaining_bytes,
					current_dg_in_buffer_size -
						remaining_bytes);
			}


			if (dg->src.context == VMCI_HYPERVISOR_CONTEXT_ID &&
			    dg->dst.resource == VMCI_EVENT_HANDLER) {
				result = vmci_event_dispatch(dg);
			} else {
				result = vmci_datagram_invoke_guest_handler(dg);
			}
			if (result < VMCI_SUCCESS)
				dev_dbg(vmci_dev->dev,
					"Datagram with resource (ID=0x%x) failed (err=%d)\n",
					 dg->dst.resource, result);


			dg = (struct vmci_datagram *)((u8 *)dg +
						      dg_in_size);
		} else {
			size_t bytes_to_skip;


			dev_dbg(vmci_dev->dev,
				"Failed to receive datagram (size=%u bytes)\n",
				 dg_in_size);

			bytes_to_skip = dg_in_size - remaining_bytes;
			if (current_dg_in_buffer_size != dg_in_buffer_size)
				current_dg_in_buffer_size = dg_in_buffer_size;

			for (;;) {
				ioread8_rep(vmci_dev->iobase +
						VMCI_DATA_IN_ADDR,
					vmci_dev->data_buffer,
					current_dg_in_buffer_size);
				if (bytes_to_skip <= current_dg_in_buffer_size)
					break;

				bytes_to_skip -= current_dg_in_buffer_size;
			}
			dg = (struct vmci_datagram *)(dg_in_buffer +
						      bytes_to_skip);
		}

		remaining_bytes =
		    (size_t) (dg_in_buffer + current_dg_in_buffer_size -
			      (u8 *)dg);

		if (remaining_bytes < VMCI_DG_HEADERSIZE) {


			ioread8_rep(vmci_dev->iobase + VMCI_DATA_IN_ADDR,
				    vmci_dev->data_buffer,
				    current_dg_in_buffer_size);
			dg = (struct vmci_datagram *)dg_in_buffer;
			remaining_bytes = current_dg_in_buffer_size;
		}
	}
}
