key(int k, int x, int y)
{
  if (k == 3 || k == 27 || k == 'q')
    exit(0);
  if (k == KEY_F(1) || k == 'h')
  {
    set_centered_pic(0);
    help("golf.html", golf_help);
  }
  if (k == KEY_F(2) || k == 'r')
  {
    set_centered_pic(0);
    start_again();
  }
  if (k == 8 || k == 127 || k == KEY_DELETE)
  {
    clear_arrows();
    supress_arrows = 1;
    set_centered_pic(0);
    stack_undo();
    show_count();
    supress_arrows = 0;
    set_arrows();
  }
  if (k == 'd')
  {
    int i;
    for (i=0; i<7; i++)
      printf("i=%d a=%d\n", i, arrows[i]);
  }
}
