show_untagged()
{
  char tmp[4];
  int i, x;
  if (untagged < 0)
    strcpy(tmp, "000");
  else
    sprintf(tmp, "%03d", untagged);
  for (i=0; i<3; i++)
  {
    x = TD_W*(tmp[i]-'0');
    put_picture(title, i*TD_W-x+x0, title_y, x, 0, TD_W, TD_H);
  }
}
