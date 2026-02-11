bgav_qt_dref_dump(int indent, qt_dref_t * c)
  {
  int i;
  bgav_diprintf(indent, "dref\n");
  bgav_diprintf(indent+2, "version:    %d\n", c->version);
  bgav_diprintf(indent+2, "flags:      %08x\n", c->flags);
  bgav_diprintf(indent+2, "table_size: %08x\n", c->table_size);
  for(i = 0; i < c->table_size; i++)
    {
    bgav_diprintf(indent+4, "Table    %d\n", i);
    bgav_diprintf(indent+4, "size:    %d\n", c->table[i].size);
    bgav_diprintf(indent+4, "type:    ");
    bgav_dump_fourcc(c->table[i].type);
    bgav_dprintf("\n");

    bgav_diprintf(indent+4, "version: %d\n", c->table[i].version);
    bgav_diprintf(indent+4, "flags:   %08x\n", c->table[i].flags);
    if(c->table[i].size > 12)
      {
      bgav_diprintf(indent+4, "data_reference:\n");
      bgav_hexdump(c->table[i].data_reference,
                   c->table[i].size-12, 16);
      }
    }
  bgav_diprintf(indent, "end of dref\n");
  }
