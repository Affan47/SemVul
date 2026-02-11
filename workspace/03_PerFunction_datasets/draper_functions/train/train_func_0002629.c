iFileCheckConvertGray(imFile* ifile, imbyte* data)
{
  int i, do_remap = 0;
  imbyte remap[256], r, g, b;


  for (i = 0; i < ifile->palette_count; i++)
  {
    imColorDecode(&r, &g, &b, ifile->palette[i]);

    if (r != i)
    {
      ifile->palette[i] = imColorEncode((imbyte)i, (imbyte)i, (imbyte)i);
      do_remap = 1;
    }

    remap[i] = r;
  }

  if (!do_remap)
    return;

  int count = ifile->width*ifile->height;
  for(i = 0; i < count; i++)
  {
    *data = remap[*data];
    data++;
  }

  int transp_count;
  imbyte* transp_map = (imbyte*)imFileGetAttribute(ifile, "TransparencyMap", NULL, &transp_count);
  if (transp_map)
  {
    imbyte new_transp_map[256];
    for (i=0; i<transp_count; i++)
      new_transp_map[i] = transp_map[remap[i]];
    imFileSetAttribute(ifile, "TransparencyMap", IM_BYTE, transp_count, new_transp_map);
  }
}
