assoc_report(int idx, int details)
{
  if (details) {
    assoc_t *a;
    int size = 0, count = 0;

    for (a = assoc; a; a = a->next) {
      count++;
      size += sizeof(assoc_t);
    }

    dprintf(idx, "    %d current association%s\n", count,
            (count != 1) ? "s" : "");
    dprintf(idx, "    Using %d byte%s of memory\n", size,
            (size != 1) ? "s" : "");
  }
}
