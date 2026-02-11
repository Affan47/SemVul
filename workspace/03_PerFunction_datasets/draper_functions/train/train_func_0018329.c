genie_eof (NODE_T * p)
{
  A68_REF ref_file;
  A68_FILE *file;
  POP_REF (p, &ref_file);
  CHECK_REF (p, ref_file, MODE (REF_FILE));
  file = FILE_DEREF (&ref_file);
  CHECK_INIT (p, INITIALISED (file), MODE (FILE));
  if (!OPENED (file)) {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_FILE_NOT_OPEN);
    exit_genie (p, A68_RUNTIME_ERROR);
  }
  if (DRAW_MOOD (file)) {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_FILE_WRONG_MOOD, "draw");
    exit_genie (p, A68_RUNTIME_ERROR);
  }
  if (WRITE_MOOD (file)) {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_FILE_WRONG_MOOD, "write");
    exit_genie (p, A68_RUNTIME_ERROR);
  } else if (READ_MOOD (file)) {
    int ch = char_scanner (file);
    PUSH_PRIMITIVE (p, (BOOL_T) ((ch == EOF_CHAR || END_OF_FILE (file)) ? A68_TRUE : A68_FALSE), A68_BOOL);
    unchar_scanner (p, file, (char) ch);
  } else {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_FILE_WRONG_MOOD, "undetermined");
    exit_genie (p, A68_RUNTIME_ERROR);
  }
}
