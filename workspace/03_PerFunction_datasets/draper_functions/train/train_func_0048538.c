lookup_converted_place(TreeNode *se_cmavo)
{
  char *se;
  int conv;

  se = cmavo_table[se_cmavo->data.cmavo.code].cmavo;
  if (!strcmp(se, "se")) {
    conv = 2;
  } else if (!strcmp(se, "te")) {
    conv = 3;
  } else if (!strcmp(se, "ve")) {
    conv = 4;
  } else if (!strcmp(se, "xe")) {
    conv = 5;
  } else {
    assert(0);
  }
  return conv;
}
