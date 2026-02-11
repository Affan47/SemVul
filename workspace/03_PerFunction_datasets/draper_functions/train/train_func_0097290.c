HandleInput(int& key, cmCursesMainForm*, WINDOW* w)
{


  if (key == 10 || key == KEY_ENTER)
    {
    if (this->GetValueAsBool())
      {
      this->SetValueAsBool(false);
      }
    else
      {
      this->SetValueAsBool(true);
      }

    touchwin(w);
    wrefresh(w);
    return true;
    }
  else
    {
    return false;
    }

}
