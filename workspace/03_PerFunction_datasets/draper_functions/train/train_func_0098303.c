key(int k, int x, int y)
{
  if (k == 3 || k == 27 || k == 'q')
    exit(0);

  set_centered_pic(0);

  if (k == KEY_F(1) || k == 'h')
  {
    help("minesweeper.html", minesweeper_help);
  }

  if (k == 'a' && penguin == PENGUIN_NORMAL)
    autoplay();
  if (k == 'A' && penguin == PENGUIN_NORMAL)
  {
    auto_play_mode = !auto_play_mode;
    autoplay();
  }

  if (k == KEY_F(2) || k == 'r')
    start_again();

  if (k >= '1' && k <= '4')
  {
    level = k - '1';
    start_again();
  }

  if (k >= '6' && k <= '9')
  {
    penguin = k - '6';
    set_penguin(penguin);
  }
}
