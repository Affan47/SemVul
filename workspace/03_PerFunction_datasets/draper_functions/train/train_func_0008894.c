isl_schedule_dump(__isl_keep isl_schedule *schedule)
{
	isl_printer *printer;

	if (!schedule)
		return;

	printer = isl_printer_to_file(isl_schedule_get_ctx(schedule), stderr);
	printer = isl_printer_set_yaml_style(printer, ISL_YAML_STYLE_BLOCK);
	printer = isl_printer_print_schedule(printer, schedule);

	isl_printer_free(printer);
}
