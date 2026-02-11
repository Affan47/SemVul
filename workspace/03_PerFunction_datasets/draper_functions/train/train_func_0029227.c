C_message(C_word msg)
{
  unsigned int n = C_header_size(msg);


  if (memchr(C_c_string(msg), '\0', n) != NULL)
    barf(C_ASCIIZ_REPRESENTATION_ERROR, "##sys#message", msg);

  if(C_gui_mode) {
    if (n >= sizeof(buffer))
      n = sizeof(buffer) - 1;
    C_strncpy(buffer, C_c_string(msg), n);
    buffer[ n ] = '\0';
#if defined(_WIN32) && !defined(__CYGWIN__)
    MessageBox(NULL, buffer, C_text("CHICKEN runtime"), MB_OK | MB_ICONEXCLAMATION);
    return C_SCHEME_UNDEFINED;
#endif
  }

  C_fwrite(C_c_string(msg), n, sizeof(C_char), stdout);
  C_putchar('\n');
  return C_SCHEME_UNDEFINED;
}
