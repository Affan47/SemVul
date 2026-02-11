script_include_directive(void* closurev, const char* filename, size_t length)
{
  Parser_closure* closure = static_cast<Parser_closure*>(closurev);
  std::string name(filename, length);
  Command_line* cmdline = closure->command_line();
  read_script_file(name.c_str(), cmdline, &cmdline->script_options(),
                   PARSING_LINKER_SCRIPT, Lex::LINKER_SCRIPT);
}
