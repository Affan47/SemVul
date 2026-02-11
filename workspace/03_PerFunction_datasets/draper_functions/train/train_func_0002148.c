on_add_a_difference_activate           (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int lp;
    for(lp=1 ; lp <= MAX_WINS;  lp ++)
      if(sp->im_widget[lp] == NULL)
	{
	  fileselection_hook=load_diff_from_file;
	  fileselection1_for_image_num_g= lp;

	  show_fs(
		  _( "load difference mesh")
#if GTK_MAJOR_VERSION >= 2
		  ,	    GTK_FILE_CHOOSER_ACTION_OPEN
#endif
		  );
	  return;
	}
}
