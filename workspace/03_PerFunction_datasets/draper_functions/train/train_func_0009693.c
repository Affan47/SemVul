change(int delta)
{
	if(_selected)
	{
		if(0 == delta)
			delta = 1;
		if(delta > 0)
			for(int i = 0; i < delta; ++i)
				_selected = _selected->next;
		else if(delta < 0)
			for(int i = 0; i > delta; --i)
				_selected = _selected->prev;
		select(_selected);
	}
	ct_widget_t::change(delta);
}
