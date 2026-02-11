show_interrupt_source_override(s_madt * madt)
{
    if (madt->interrupt_source_override_count == 0) {
	more_printf("No interrupt source override found\n");
	return;
    }


    for (int i = 0; i < madt->interrupt_source_override_count; i++) {
	s_interrupt_source_override *siso = &madt->interrupt_source_override[i];
	char buffer[20];
	char bus_type[10];
	memset(bus_type, 0, sizeof(bus_type));

	if (siso->bus == 0)
	    strcpy(bus_type, "ISA");
	else
	    strcpy(bus_type, "unknown");

	more_printf("INT_SRC_OVR (bus %s (%d) bus_irq %d global_irq %d %s)\n",
		    bus_type, siso->bus, siso->source,
		    siso->global_system_interrupt, flags_to_string(buffer,
								   siso->
								   flags));
    }
}
