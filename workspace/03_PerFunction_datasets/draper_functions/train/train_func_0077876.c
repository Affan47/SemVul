set_visible_all(bool b)
{
  set_visible(b);
   for(lwb::iterator i=list_wb_.begin();i!=list_wb_.end();i++)
     (*i)->set_visible(b);
}
