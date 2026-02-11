parse_just_symbols(const char*, const char* arg,
				    Command_line* cmdline)
{
  Input_file_argument file(arg, Input_file_argument::INPUT_FILE_TYPE_FILE,
			   "", true, *this);
  cmdline->inputs().add_file(file);
}
