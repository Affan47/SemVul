alog_response_size_clf(FILE *fp, struct alog_instr *instr,
		       int argc, char **argv)
{
    char buf[UINTMAX_STRSIZE_BOUND];
    if (total_bytes_out)
	print_str(fp, umaxtostr(total_bytes_out, buf));
    else
	print_str(fp, "-");
}
