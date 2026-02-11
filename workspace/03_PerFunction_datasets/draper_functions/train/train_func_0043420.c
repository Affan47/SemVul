mapimg_reset(void)
{
  if (!mapimg_initialised()) {
    return;
  }

  if (mapdef_list_size(mapimg.mapdef) > 0) {
    mapdef_list_iterate(mapimg.mapdef, pmapdef) {
      mapdef_list_remove(mapimg.mapdef, pmapdef);
      mapdef_destroy(pmapdef);
    } mapdef_list_iterate_end;
  }
}
