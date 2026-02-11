gst_asm_scan_next_token (GstASMScan * scan)
{
  gchar ch;

  ch = THIS_CHAR (scan);


  while (IS_SPACE (ch))
    ch = NEXT_CHAR (scan);


  while (ch == '\\')
    ch = NEXT_CHAR (scan);

  switch (ch) {
    case '#':
      scan->token = GST_ASM_TOKEN_HASH;
      NEXT_CHAR (scan);
      break;
    case ';':
      scan->token = GST_ASM_TOKEN_SEMICOLON;
      NEXT_CHAR (scan);
      break;
    case ',':
      scan->token = GST_ASM_TOKEN_COMMA;
      NEXT_CHAR (scan);
      break;
    case '=':
      scan->token = GST_ASM_TOKEN_EQUAL;
      if (NEXT_CHAR (scan) == '=')
        NEXT_CHAR (scan);
      break;
    case '!':
      if (NEXT_CHAR (scan) == '=') {
        scan->token = GST_ASM_TOKEN_NOTEQUAL;
        NEXT_CHAR (scan);
      }
      break;
    case '&':
      scan->token = GST_ASM_TOKEN_AND;
      if (NEXT_CHAR (scan) == '&')
        NEXT_CHAR (scan);
      break;
    case '|':
      scan->token = GST_ASM_TOKEN_OR;
      if (NEXT_CHAR (scan) == '|')
        NEXT_CHAR (scan);
      break;
    case '<':
      scan->token = GST_ASM_TOKEN_LESS;
      if (NEXT_CHAR (scan) == '=') {
        scan->token = GST_ASM_TOKEN_LESSEQUAL;
        NEXT_CHAR (scan);
      }
      break;
    case '>':
      scan->token = GST_ASM_TOKEN_GREATER;
      if (NEXT_CHAR (scan) == '=') {
        scan->token = GST_ASM_TOKEN_GREATEREQUAL;
        NEXT_CHAR (scan);
      }
      break;
    case '$':
      scan->token = GST_ASM_TOKEN_DOLLAR;
      NEXT_CHAR (scan);
      break;
    case '(':
      scan->token = GST_ASM_TOKEN_LPAREN;
      NEXT_CHAR (scan);
      break;
    case ')':
      scan->token = GST_ASM_TOKEN_RPAREN;
      NEXT_CHAR (scan);
      break;
    case '"':
      NEXT_CHAR (scan);
      gst_asm_scan_string (scan, '"');
      break;
    case '\'':
      NEXT_CHAR (scan);
      gst_asm_scan_string (scan, '\'');
      break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      gst_asm_scan_number (scan);
      break;
    case '\0':
      scan->token = GST_ASM_TOKEN_EOF;
      break;
    default:
      gst_asm_scan_identifier (scan);
      break;
  }
  gst_asm_scan_print_token (scan);
  return scan->token;
}
