iImageGLSetTranspMap(imbyte *map, imbyte *gldata, int count, imbyte *transp_map, int transp_count)
{

  gldata += 3;
  for(int i = 0; i < count; i++)
  {
    if (*map < transp_count)
      *gldata = transp_map[*map];
    else
      *gldata = 255;

    map++;
    gldata += 4;
  }
}
