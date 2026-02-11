update_interrupts(void)
{

	if (tms34061.intf.interrupt)
	{

		if ((tms34061.regs[TMS34061_STATUS] & 0x0001) && (tms34061.regs[TMS34061_CONTROL1] & 0x0400))
			(*tms34061.intf.interrupt)(ASSERT_LINE);
		else
			(*tms34061.intf.interrupt)(CLEAR_LINE);
	}
}
