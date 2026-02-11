mac_close (gcry_mac_hd_t hd)
{
  if (hd->spec->ops->close)
    hd->spec->ops->close (hd);

  wipememory (hd, sizeof (*hd));

  xfree (hd);
}
