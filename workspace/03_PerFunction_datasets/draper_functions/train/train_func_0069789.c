isl_set_print(struct isl_set *set, FILE *out, int indent,
	unsigned output_format)
{
	isl_printer *printer;

	if (!set)
		return;

	printer = isl_printer_to_file(set->ctx, out);
	printer = isl_printer_set_indent(printer, indent);
	printer = isl_printer_set_output_format(printer, output_format);
	printer = isl_printer_print_set(printer, set);

	isl_printer_free(printer);
}
