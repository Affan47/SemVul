genie_reset (NODE_T * p)
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
  if (!RESET (&CHANNEL (file))) {
    diagnostic_node (A68_RUNTIME_ERROR, p, ERROR_FILE_CANT_RESET);
    exit_genie (p, A68_RUNTIME_ERROR);
  }
  if (IS_NIL (STRING (file))) {
    close_file_entry (p, FILE_ENTRY (file));
  } else {
    STRPOS (file) = 1;
  }
  READ_MOOD (file) = A68_FALSE;
  WRITE_MOOD (file) = A68_FALSE;
  CHAR_MOOD (file) = A68_FALSE;
  DRAW_MOOD (file) = A68_FALSE;
  FD (file) = A68_NO_FILENO;

}
