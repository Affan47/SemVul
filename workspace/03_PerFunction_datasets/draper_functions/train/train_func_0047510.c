data_read(void)
{
  struct record *rec;
  pdbrec_t *pdb_rec;
  int	i;

  if ((file_in->creator != MYCREATOR) || (file_in->type != MYTYPE)) {
    fatal(MYNAME ": Not a QuoVadis file.\n");
  }


  for (pdb_rec = file_in->rec_list->next; pdb_rec; pdb_rec = pdb_rec->next) {
    int num_recs = pdb_rec->size / sizeof(struct record);
    for (i = 0; i < num_recs; i++) {
      waypoint *wpt_tmp;

      wpt_tmp = waypt_new();

      rec = (struct record *)
            &(pdb_rec->data[i * sizeof(struct record)]);

      wpt_tmp->longitude =
        (be_read32(&rec->longitude) / 1000000.0) - 180.0;
      wpt_tmp->latitude =
        90.0 - (be_read32(&rec->latitude) / 1000000.0);
      wpt_tmp->shortname = xstrdup(rec->name);

      waypt_alloc_gc_data(wpt_tmp)->type =
        icon_to_wpt(be_read16(&rec->icon_bitmap));

      waypt_add(wpt_tmp);
    }
  }
}
