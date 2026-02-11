serial_init (void)
{
#ifdef SERIAL_PORT
	if (!currprefs.use_serial)
		return;
	if (!currprefs.serial_demand)
		serial_open ();
#endif
}
