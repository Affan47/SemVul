gst_asm_scan_identifier (GstASMScan * scan)
{
  gchar ch;
  gint i = 0;

  ch = THIS_CHAR (scan);

  while ((IS_CHAR (ch) || IS_SPACE (ch))) {
    if (i < (MAX_RULE_LENGTH - 1) && !IS_SPACE (ch))
      scan->val[i++] = ch;
    ch = NEXT_CHAR (scan);
  }
  scan->val[i] = '\0';

  scan->token = GST_ASM_TOKEN_IDENTIFIER;
}
