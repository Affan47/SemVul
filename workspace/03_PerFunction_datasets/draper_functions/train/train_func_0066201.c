parse_mos(int level)
{
  uchar data[64];
  int skip, save;
  char *cp;

  save = ftell(ifp);
  while (1) {
    fread (data, 1, 8, ifp);
    if (strcmp(data,"PKTS")) break;
    strcpy (model, "Valeo");
    printf ("%*s%s ", level, "", data);
    fread (data, 1, 40, ifp);
    skip = fget4(ifp);
    printf ("%s %d bytes: ", data, skip);
    if (!strcmp(data,"JPEG_preview_data")) {
      thumb_head[0] = 0;
      thumb_offset = ftell(ifp);
      thumb_length = skip;
    }
    fread (data, 1, 64, ifp);
    fseek (ifp, -64, SEEK_CUR);
    data[63] = 0;
    while ((cp=index(data,'\n')))
      *cp = ' ';
    printf ("%s\n",data);
    parse_mos(level+2);
    fseek (ifp, skip, SEEK_CUR);
  }
  fseek (ifp, save, SEEK_SET);
}
