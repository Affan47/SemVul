show_dmi_battery(int argc __unused, char **argv __unused,
			     struct s_hardware *hardware)
{
    if (hardware->dmi.battery.filled == false) {
	more_printf("battery information not found on your system, see "
		    "`show list' to see which module is available.\n");
	return;
    }
    reset_more_printf();
    more_printf("Battery \n");
    more_printf(" Vendor             : %s\n",
		hardware->dmi.battery.manufacturer);
    more_printf(" Manufacture Date   : %s\n",
		hardware->dmi.battery.manufacture_date);
    more_printf(" Serial             : %s\n", hardware->dmi.battery.serial);
    more_printf(" Name               : %s\n", hardware->dmi.battery.name);
    more_printf(" Chemistry          : %s\n", hardware->dmi.battery.chemistry);
    more_printf(" Design Capacity    : %s\n",
		hardware->dmi.battery.design_capacity);
    more_printf(" Design Voltage     : %s\n",
		hardware->dmi.battery.design_voltage);
    more_printf(" SBDS               : %s\n", hardware->dmi.battery.sbds);
    more_printf(" SBDS Manuf. Date   : %s\n",
		hardware->dmi.battery.sbds_manufacture_date);
    more_printf(" SBDS Chemistry     : %s\n",
		hardware->dmi.battery.sbds_chemistry);
    more_printf(" Maximum Error      : %s\n",
		hardware->dmi.battery.maximum_error);
    more_printf(" OEM Info           : %s\n", hardware->dmi.battery.oem_info);
}
