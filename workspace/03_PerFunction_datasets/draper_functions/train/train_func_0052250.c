xbsd_link_part (void)
{
  int k, i;
  struct partition *p;

  k = get_partition (1, partitions);

  if (!xbsd_check_new_partition (&i))
    return;

  p = get_part_table(k);

  xbsd_dlabel.d_partitions[i].p_size   = get_nr_sects(p);
  xbsd_dlabel.d_partitions[i].p_offset = get_start_sect(p);
  xbsd_dlabel.d_partitions[i].p_fstype = xbsd_translate_fstype(p->sys_ind);
}
