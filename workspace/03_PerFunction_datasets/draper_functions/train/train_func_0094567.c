update_layout()
{

  u_int16 indice_h=space_with_border_;

  switch(layout_)
    {
    case LIST_LAYOUT:

      for(lwb::iterator i=list_wb_.begin();i!=list_wb_.end();i++)
	{
	  (*i)->move((*i)->x(),indice_h);

	  indice_h+=(*i)->height()+space_with_object_;
	}

      break;
    }
}
