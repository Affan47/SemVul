spi_get_root_window ()
{
	if (!default_display)
		spi_set_display (NULL);

        return DefaultRootWindow (default_display);
}
