fixed_gcry_pth_init (void)
{
  return pth_self ()? 0 : (pth_init () == FALSE) ? errno : 0;
}
