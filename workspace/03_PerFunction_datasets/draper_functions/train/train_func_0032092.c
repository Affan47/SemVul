cd_set_volume(int cd_desc, struct disc_volume vol)
{
  struct CDAUDIO_VOLCTRL cdvol;
#ifdef CDAUDIO_VOLCTRL_DATA
  struct cd_playback cdvol_data;
  cdvol.CDVOLCTRL_DATA = &cdvol_data;
  cdvol.CDVOLCTRL_DATA_LEN = sizeof(cdvol_data);
#endif

#define OUTOFRANGE(x) (x > 255 || x < 0)
  if(OUTOFRANGE(vol.vol_front.left) || OUTOFRANGE(vol.vol_front.right) ||
     OUTOFRANGE(vol.vol_back.left) || OUTOFRANGE(vol.vol_back.right))
    return -1;
#undef OUTOFRANGE

  cdvol.CDVOLCTRL_FRONT_LEFT = vol.vol_front.left;
  cdvol.CDVOLCTRL_FRONT_RIGHT = vol.vol_front.right;
  cdvol.CDVOLCTRL_BACK_LEFT = vol.vol_back.left;
  cdvol.CDVOLCTRL_BACK_RIGHT = vol.vol_back.right;

#ifdef CDAUDIO_VOLCTRL_SELECT
  cdvol_data.CDVOLCTRL_FRONT_LEFT_SELECT = CDAUDIO_MAX_VOLUME;
  cdvol_data.CDVOLCTRL_FRONT_RIGHT_SELECT = CDAUDIO_MAX_VOLUME;
  cdvol_data.CDVOLCTRL_BACK_LEFT_SELECT = CDAUDIO_MAX_VOLUME;
  cdvol_data.CDVOLCTRL_BACK_RIGHT_SELECT = CDAUDIO_MAX_VOLUME;
#endif

  if(ioctl(cd_desc, CDAUDIO_SET_VOLUME, &cdvol) < 0)
    return -1;

  return 0;
}
