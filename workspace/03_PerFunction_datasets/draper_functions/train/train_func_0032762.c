gtpfunc_komi(const std::string &str, size_t i,
		     bool has_id, unsigned id)
{
	i = skip_space(str, i);
	throw_syntax_error_if_end_of_line(str, i);
	i = read_float(str, i, komi);
	throw_if_extra_argument(str, i);
	output_response("", has_id, id);
}
