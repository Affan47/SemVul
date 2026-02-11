VIGRA_RGBE_ReadHeader(FILE *fp, int *width, int *height, vigra_rgbe_header_info *info)
{
  char buf[128];
  float tempf;
  int i;

  if (info) {
    info->valid = 0;
    info->programtype[0] = 0;
    info->gamma = info->exposure = 1.0;
  }
  if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == NULL)
    return rgbe_error(rgbe_read_error,NULL);

  if ((buf[0] != '#')||(buf[1] != '?')) {


  }
  else if (info) {
    info->valid |= VIGRA_RGBE_VALID_PROGRAMTYPE;
    for(i=0;i<sizeof(info->programtype)-1;i++) {
      if ((buf[i+2] == 0) || isspace(buf[i+2]))
    break;
      info->programtype[i] = buf[i+2];
    }
    info->programtype[i] = 0;
    if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
      return rgbe_error(rgbe_read_error,NULL);
  }

  for(;;) {
    if ((buf[0] == 0)||(buf[0] == '\n'))
      return rgbe_error(rgbe_format_error,"no FORMAT specifier found");
    else if (strcmp(buf,"FORMAT=32-bit_rle_rgbe\n") == 0)
      break;
    else if (info && (sscanf(buf,"GAMMA=%g",&tempf) == 1)) {
      info->gamma = tempf;
      info->valid |= VIGRA_RGBE_VALID_GAMMA;
    }
    else if (info && (sscanf(buf,"EXPOSURE=%g",&tempf) == 1)) {
      info->exposure = tempf;
      info->valid |= VIGRA_RGBE_VALID_EXPOSURE;
    }
    if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
      return rgbe_error(rgbe_read_error,NULL);
  }

#if 0
  if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
    return rgbe_error(rgbe_read_error,NULL);
  if (strcmp(buf,"\n") != 0)
    return rgbe_error(rgbe_format_error,
              "missing blank line after FORMAT specifier");
#endif

  for(;;) {
    if (fgets(buf,sizeof(buf)/sizeof(buf[0]),fp) == 0)
      return rgbe_error(rgbe_read_error,NULL);

    if (sscanf(buf,"-Y %d +X %d",height,width) == 2)
      break;
  }

  return VIGRA_RGBE_RETURN_SUCCESS;
}
