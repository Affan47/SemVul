on_add_an_image_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
    int lp;
    for(lp=1 ; lp <= MAX_WINS;  lp ++)
      if(sp->im_widget[lp] == NULL)
	{


	  sp->max_wins++;

	  create_and_show_image_win(lp);
	  setup_handlebox_factor(lp,FALSE);
	  return;
	}
}
