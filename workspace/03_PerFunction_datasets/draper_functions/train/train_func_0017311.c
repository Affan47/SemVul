print_main_header(em_state *state)
{
#if HAVE_INT_64
#define MAX_WORD_SZ_STR "64"
#else
#define MAX_WORD_SZ_STR "32"
#endif
    em_area area = {NULL, 0};
    char *format1 =
	"> emem version:            " EMEM_VSN_STR "\n"
	"> Nodename:                %s\n"
	"> Hostname:                %s\n"
	"> Pid:                     %s\n"
	"> Start time (UTC):        ";
    char *format2 = "%4.4" USGND_INT_32_FSTR
	"-%2.2" USGND_INT_32_FSTR "-%2.2" USGND_INT_32_FSTR
	" %2.2" USGND_INT_32_FSTR ":%2.2" USGND_INT_32_FSTR
	":%2.2" USGND_INT_32_FSTR ".%6.6" USGND_INT_32_FSTR "\n";
    char *format3 =
	"> Trace parser version:    %" USGND_INT_32_FSTR ".%" USGND_INT_32_FSTR
	    "\n"
	"> Actual trace version:    %" USGND_INT_32_FSTR ".%" USGND_INT_32_FSTR
	    "\n"
	"> Maximum trace word size: " MAX_WORD_SZ_STR " bits\n"
	"> Actual trace word size:  %d bits\n";
    size_t size = (strlen(format1) +
		   (state->trace_info.start_time.month
		    ? (strlen(format2) + 7*10)
		    : 1)
		   + strlen(format3)
		   + strlen(state->trace_info.nodename)
		   + strlen(state->trace_info.hostname)
		   + strlen(state->trace_info.pid)
		   + 5*10 + 1);

    if (state->output.verbose) {
	size += write_allocator_info(state, NULL);
    }

    size += write_header(state, NULL, 0);


    get_next_write_area(&area, state, &state->output.queue, size);

    area.size = sprintf(area.ptr,
			format1,
			state->trace_info.nodename,
			state->trace_info.hostname,
			state->trace_info.pid);
    if (state->trace_info.start_time.month)
	area.size += sprintf(area.ptr + area.size,
			     format2,
			     state->trace_info.start_time.year,
			     state->trace_info.start_time.month,
			     state->trace_info.start_time.day,
			     state->trace_info.start_time.hour,
			     state->trace_info.start_time.minute,
			     state->trace_info.start_time.second,
			     state->trace_info.start_time.micro_second);
    else
	*(area.ptr + area.size++) = '\n';
    area.size += sprintf(area.ptr + area.size,
			 format3,
			 state->trace_info.version.parser.major,
			 state->trace_info.version.parser.minor,
			 state->trace_info.version.trace.major,
			 state->trace_info.version.trace.minor,
			 state->trace_info.bits);

    if (state->output.verbose) {
	area.size += write_allocator_info(state, area.ptr + area.size);
    }

    area.size += write_header(state, area.ptr + area.size, 0);


    wrote_area(&area, state, &state->output.queue);
#undef MAX_WORD_SZ_STR
}
