mmo_rd_init(const char* fname)
{
  int i;

  fin = gbfopen_le(fname, "rb", MYNAME);

  category_ids = avltree_init(0, MYNAME);
  objects = avltree_init(0, MYNAME);
  icons = avltree_init(0, MYNAME);

  ico_object_id = pos_object_id = txt_object_id = cat_object_id = 0;
  wpt_object_id = rte_object_id = trk_object_id = 0;

  mmo_object_id = 0x8001;

  i = 0;
  while (mmo_icon_value_table[i].icon) {
    mmo_register_icon(mmo_icon_value_table[i].value, mmo_icon_value_table[i].icon);
    i++;
  }
}
