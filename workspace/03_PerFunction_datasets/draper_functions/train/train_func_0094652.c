examine_stack (FILE_T f, ADDR_T a68g_link, char *sym, int *printed)
{
  if (a68g_link > 0) {
    int dynamic_a68g_link = FRAME_DYNAMIC_LINK (a68g_link);
    NODE_T *p = FRAME_TREE (a68g_link);
    if (p != NO_NODE) {
      TABLE_T *q = TABLE (p);
      examine_tags (f, p, a68g_link, IDENTIFIERS (q), sym, printed);
      examine_tags (f, p, a68g_link, OPERATORS (q), sym, printed);
    }
    examine_stack (f, dynamic_a68g_link, sym, printed);
  }
}
