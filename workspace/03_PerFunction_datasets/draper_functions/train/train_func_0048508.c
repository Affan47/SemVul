trace_machine_code(struct compilation_unit *cu)
{
	void *start, *end;

	if (!cu_matches_regex(cu))
		return;

	trace_printf("Disassembler Listing:\n\n");

	start  = buffer_ptr(cu->objcode);
	end = buffer_current(cu->objcode);

	disassemble(cu, start, end);
	trace_printf("\n");
}
