unzoom()
{
	if(full_screen && gmp_embed)
	{
		menubar->show();
		toolbar->show();


		menu_tool_box->show();
		if(!channels_hide)
			channels_box->show();
		this->unfullscreen();
		full_screen=false;
	}


}
