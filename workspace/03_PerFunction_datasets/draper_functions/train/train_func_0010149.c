draw()
{
  Fl_Widget	*kid;


  kid = value();

  if (damage() & FL_DAMAGE_ALL)
  {

    if (kid)
    {
      draw_box(box(), x(), y(), w(), h(), kid->color());
      draw_child(*kid);
    }
    else
      draw_box(box(), x(), y(), w(), h(), color());

  }
  else if (kid)
    update_child(*kid);
}
