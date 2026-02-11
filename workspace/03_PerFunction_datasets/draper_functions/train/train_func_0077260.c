main(int  argc,
     char *argv[])
{
  Fl_Window	*window;
  Fl_Button	*button;
  Fl_File_Icon	*icon;


  Fl::scheme(NULL);
  Fl_File_Icon::load_system_icons();

  fc = new Fl_File_Chooser(".", "*", Fl_File_Chooser::SINGLE, "Fl_File_Chooser Test");
  fc->callback(fc_callback);


  Fl_Shared_Image::add_handler(pdf_check);
  Fl_Shared_Image::add_handler(ps_check);


  window = new Fl_Window(400, 200, "File Chooser Test");

  filter = new Fl_Input(50, 10, 315, 25, "Filter:");
  if (argc > 1)
    filter->value(argv[1]);
  else
    filter->value("PDF Files (*.pdf)\t"
                  "PostScript Files (*.ps)\t"
		  "Image Files (*.{bmp,gif,jpg,png})\t"
		  "C/C++ Source Files (*.{c,C,cc,cpp,cxx})");

  button = new Fl_Button(365, 10, 25, 25);
  button->labelcolor(FL_YELLOW);
  button->callback((Fl_Callback *)show_callback);

  icon   = Fl_File_Icon::find(".", Fl_File_Icon::DIRECTORY);
  icon->label(button);

  button = new Fl_Light_Button(50, 45, 80, 25, "MULTI");
  button->callback((Fl_Callback *)multi_callback);

  button = new Fl_Light_Button(140, 45, 90, 25, "CREATE");
  button->callback((Fl_Callback *)create_callback);

  button = new Fl_Light_Button(240, 45, 115, 25, "DIRECTORY");
  button->callback((Fl_Callback *)dir_callback);

  files = new Fl_File_Browser(50, 80, 340, 75, "Files:");
  files->align(FL_ALIGN_LEFT);

  button = new Fl_Button(340, 165, 50, 25, "Close");
  button->callback((Fl_Callback *)close_callback);

  window->resizable(files);
  window->end();
  window->show(1, argv);

  Fl::run();

  return (0);
}
