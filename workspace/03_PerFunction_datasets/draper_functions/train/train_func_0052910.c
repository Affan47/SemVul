cd_get_volume(int cd_desc, struct disc_volume *vol)
{
#ifdef CDAUDIO_GET_VOLUME
  struct CDAUDIO_VOLSTAT cdvol;
#ifdef CDAUDIO_VOLSTAT_DATA
  struct CDAUDIO_VOLSTAT_DATA cdvol_data;
  cdvol.CDVOLSTAT_DATA = &cdvol_data;
  cdvol.CDVOLSTAT_DATA_LEN = sizeof(cdvol_data);
#endif

  if(ioctl(cd_desc, CDAUDIO_GET_VOLUME, &cdvol) < 0)
    return -1;

#ifdef CDAUDIO_VOLSTAT_DATA
#define CDV cdvol_data
#else
#define CDV cdvol
#endif
  vol->vol_front.left = CDV.CDVOLSTAT_FRONT_LEFT;
  vol->vol_front.right = CDV.CDVOLSTAT_FRONT_RIGHT;
  vol->vol_back.left = CDV.CDVOLSTAT_BACK_LEFT;
  vol->vol_back.right = CDV.CDVOLSTAT_BACK_RIGHT;
#undef CDV

  return 0;
#else
  errno = ENOTTY;
  return -1;
#endif
}
