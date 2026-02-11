gamgi_mesa_select_new (unsigned char *color)
{
unsigned char *rgb = gamgi->rgb;


rgb[2] += 1 << gamgi->b;
if (rgb[2] == 0)
  {
  rgb[1] += 1 << gamgi->g;
  if (rgb[1] == 0)
    {
    rgb[0] += 1 << gamgi->r;
    if (rgb[0] == 0)
      {


      return FALSE;
      }
    }
  }

color[0] = rgb[0];
color[1] = rgb[1];
color[2] = rgb[2];

return TRUE;
}
