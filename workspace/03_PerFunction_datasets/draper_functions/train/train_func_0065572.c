icp_a106_vbar (Driver *drvthis, int x, int y, int len, int promille, int options)
{
  int total_pixels = ((long) 2 * len * LCD_DEFAULT_CELLHEIGHT + 1 ) * promille / 2000;
  int pos;
  static char map[] = " __---=#";

  for (pos = 0; pos < len; pos ++) {
    int pixels = total_pixels - LCD_DEFAULT_CELLHEIGHT * pos;

    if (pixels >= LCD_DEFAULT_CELLHEIGHT) {

      icp_a106_icon(drvthis, x, y-pos, ICON_BLOCK_FILLED);
    }
    else {

      icp_a106_chr(drvthis, x, y-pos, map[pixels]);
      break;
    }
  }
}
