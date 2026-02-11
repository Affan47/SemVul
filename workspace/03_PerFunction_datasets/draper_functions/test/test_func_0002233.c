load_cmos(const int cmos_size)
{
  int i;
  set_permissions();
  for (i=0;i<cmos_size;i++)
    cmos[i]=read_cmos(i);
  unset_permissions();
  return 0;
}
