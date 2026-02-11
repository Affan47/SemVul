term_nuke(term *t)
{

	if (t->active_flag)
	{

		if (t->nuke_hook) (*t->nuke_hook)(t);


		t->active_flag = FALSE;


		t->mapped_flag = FALSE;
	}


	term_win_nuke(t->old);


	FREE(t->old);


	term_win_nuke(t->scr);


	FREE(t->scr);


	if (t->mem)
	{

		term_win_nuke(t->mem);


		FREE(t->mem);
	}


	if (t->tmp)
	{

		term_win_nuke(t->tmp);


		FREE(t->tmp);
	}


	FREE(t->x1);
	FREE(t->x2);


	FREE(t->key_queue);


	return (0);
}
