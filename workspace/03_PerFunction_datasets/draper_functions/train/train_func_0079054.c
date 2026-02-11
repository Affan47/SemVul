calculate_driver_mask()
{
    driver_mask = 0;
    if (requirement_contains(requirements, "userlevel"))
	driver_mask |= 1 << Driver::USERLEVEL;
    if (requirement_contains(requirements, "linuxmodule"))
	driver_mask |= 1 << Driver::LINUXMODULE;
    if (requirement_contains(requirements, "bsdmodule"))
	driver_mask |= 1 << Driver::BSDMODULE;
    if (requirement_contains(requirements, "ns"))
	driver_mask |= 1 << Driver::NSMODULE;
    if (driver_mask == 0)
	driver_mask = Driver::ALLMASK;
    if (requirement_contains(requirements, "multithread"))
	driver_mask |= 1 << Driver::MULTITHREAD;
}
