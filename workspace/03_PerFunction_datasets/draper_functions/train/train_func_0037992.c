create_mouse (int button, int state, int x, int y)
{
  float rx = (float) x / width;
  float ry = (float) y / height;
  missionmenuitemselected = -1;

  if (ry >= 0.8 && ry <= 0.9)
  {
    if (rx >= 0.4 && rx <= 0.6)
    {
      missionmenuitemselected = 0;
      if (state == MOUSE_DOWN)
      {
        create_key (27, 0, 0);
      }
    }
  }
}
