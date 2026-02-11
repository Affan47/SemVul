colour_heap (ADDR_T fp)
{
  while (fp != 0) {
    NODE_T *p = FRAME_TREE (fp);
    TABLE_T *q = TABLE (p);
    if (q != NO_TABLE) {
      TAG_T *i;
      for (i = IDENTIFIERS (q); i != NO_TAG; FORWARD (i)) {
        colour_object (FRAME_LOCAL (fp, OFFSET (i)), MOID (i));
      }
      for (i = ANONYMOUS (q); i != NO_TAG; FORWARD (i)) {
        if (PRIO (i) == GENERATOR) {
          colour_object (FRAME_LOCAL (fp, OFFSET (i)), MOID (i));
        }
      }
    }
    fp = FRAME_DYNAMIC_LINK (fp);
  }
}
