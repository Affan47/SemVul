oldapcsetup(void)
{
	int	ret = 0;


	ret = query_ups("ups.model", 1);

	if (ret != 1) {

		dstate_setinfo("ups.model", "Smart-UPS");
	}


	if (query_ups("output.current", 1))
		dstate_setinfo("ups.model", "Matrix-UPS");

	query_ups("ups.serial", 1);
	query_ups("input.voltage", 1);

	update_status();


}
