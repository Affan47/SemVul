previous()
{
  if(cur_select_==list_wb_.end() || list_wb_.size() == 0) return;

  audio::play_wave (-1, 1);
  (*cur_select_)->on_unselect();


  rules(false,*cur_select_);

  (*cur_select_)->set_activate (false);

  lwb::iterator i=cur_select_;

  if(circle_)
    {
      if(i==list_wb_.begin()) i=list_wb_.end();
      i--;
    }
  else if(i!=list_wb_.begin()) i--;

  while(i != list_wb_.begin() && !(*i)->is_can_be_selected() && i != cur_select_) i--;

  if( i== list_wb_.begin() && !(*i)->is_can_be_selected())
    {
      if(circle_)
	{
	  i = list_wb_.end();
	  i--;
	  while(i!=list_wb_.begin() && !(*i)->is_can_be_selected() && i!=cur_select_) i--;
	  if((*i)->is_can_be_selected()) cur_select_=i;
	}
    } else cur_select_=i;

  (*cur_select_)->on_select();


  rules(true,*cur_select_);


  on_previous();

  finish_scroll_ =false;

}
