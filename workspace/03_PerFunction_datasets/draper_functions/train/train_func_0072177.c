snap_pic (int fd)
{

  char f[] = "snap_pic";


  if (change_res (Camera.fd, dc210_opt_lowres) == -1)
    {
      DBG (1, "%s: Failed to set resolution\n", f);
      return SANE_STATUS_INVAL;
    }


  if (send_pck (fd, shoot_pck) == -1)
    {
      DBG (4, "%s: error: send_pck returned -1\n", f);
      return SANE_STATUS_INVAL;
    }
  else
    {
      if (end_of_data (Camera.fd) == -1)
	{
	  DBG (2, "%s: error: end_of_data returned -1\n", f);
	  return SANE_STATUS_INVAL;
	}
    }
  Camera.pic_taken++;
  Camera.pic_left--;
  Camera.current_picture_number = Camera.pic_taken;
  image_range.max++;
  sod[DC210_OPT_IMAGE_NUMBER].cap &= ~SANE_CAP_INACTIVE;


  if ((Camera.Pictures =
       (PictureInfo *) realloc (Camera.Pictures,
				Camera.pic_taken * sizeof (PictureInfo))) ==
      NULL)
    {
      DBG (4, "%s: error: allocate memory for pictures array\n", f);
      return SANE_STATUS_INVAL;
    }

  if (get_picture_info (Camera.Pictures + Camera.pic_taken,
			Camera.pic_taken) == -1)
    {
      DBG (1, "%s: Failed to get new picture info\n", f);

      return SANE_STATUS_INVAL;
    }

  return SANE_STATUS_GOOD;
}
