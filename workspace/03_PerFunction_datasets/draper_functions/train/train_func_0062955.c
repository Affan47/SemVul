set_border(win_theme & wt, u_int8 size)
{
  switch(size)
    {
    case NORMAL:
      *this=*(wt.normal);
      break;

    case MINI:
      *this=*(wt.mini);
      break;
    }
  refresh();
}
