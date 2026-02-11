create_sysfs_attrs(struct usb_serial_port *port)
{
	struct ftdi_private *priv = usb_get_serial_port_data(port);
	int retval = 0;


	if (priv->chip_type != SIO) {
		dev_dbg(&port->dev, "sysfs attributes for %s\n", ftdi_chip_name[priv->chip_type]);
		retval = device_create_file(&port->dev, &dev_attr_event_char);
		if ((!retval) &&
		    (priv->chip_type == FT232BM ||
		     priv->chip_type == FT2232C ||
		     priv->chip_type == FT232RL ||
		     priv->chip_type == FT2232H ||
		     priv->chip_type == FT4232H ||
		     priv->chip_type == FT232H ||
		     priv->chip_type == FTX)) {
			retval = device_create_file(&port->dev,
						    &dev_attr_latency_timer);
		}
	}
	return retval;
}
