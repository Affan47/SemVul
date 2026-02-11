hideSubmenus()
{
	list<BaseMenuItem*> temp_mi;
	list<BaseMenuItem*>::iterator it;

	for(it = mi.begin(); it != mi.end(); it++)
	{
		if ((*it)->sub && (*it)->sub->is_visible)
		{
			(*it)->sub->hide((*it)->sub);

			temp_mi = (*it)->sub->mi;


			LOOP:


			list<BaseMenuItem*>::iterator n_it;
			for(n_it = temp_mi.begin(); n_it != temp_mi.end(); n_it++)
			{
				if((*n_it)->sub && (*n_it)->sub->is_visible)
				{
					(*n_it)->sub->hide((*n_it)->sub);

					temp_mi = (*n_it)->sub->mi;


					goto LOOP;
				}
			}
		}
	}

}
