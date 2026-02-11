fh_dma (format_data_t form, int argc, char *argv[])
{
  if (form->ifr->ifr_map.dma)
    put_int (form, argc, argv, form->ifr->ifr_map.dma);
  else
    put_string (form, "(not available)");
}
