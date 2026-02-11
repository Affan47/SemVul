usb_serial_operations_init(struct usb_serial_driver *device)
{
	set_to_generic_if_null(device, open);
	set_to_generic_if_null(device, write);
	set_to_generic_if_null(device, close);
	set_to_generic_if_null(device, write_room);
	set_to_generic_if_null(device, chars_in_buffer);
	if (device->tx_empty)
		set_to_generic_if_null(device, wait_until_sent);
	set_to_generic_if_null(device, read_bulk_callback);
	set_to_generic_if_null(device, write_bulk_callback);
	set_to_generic_if_null(device, process_read_urb);
	set_to_generic_if_null(device, prepare_write_buffer);
}
