ReleaseDeviceInterface(void)
{
	Interface::Print("Releasing device interface...\n");

	libusb_release_interface(deviceHandle, interfaceIndex);

#ifdef OS_LINUX

	if (detachedDriver)
	{
		Interface::Print("Re-attaching kernel driver...\n");
		libusb_attach_kernel_driver(deviceHandle, interfaceIndex);
	}

#endif

	interfaceClaimed = false;
	Interface::Print("\n");
}
