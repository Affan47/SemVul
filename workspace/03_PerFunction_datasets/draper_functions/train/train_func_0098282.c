option_lexer_init(char* filename) {
  option_lloc.first_line = 1;
  option_lloc.first_column = 1;
  option_lloc.last_line = 1;
  option_lloc.last_column = 1;
  if ((option_in = fopen(filename, "r"))) {
    option_filename = strdup(filename);
  }
}
