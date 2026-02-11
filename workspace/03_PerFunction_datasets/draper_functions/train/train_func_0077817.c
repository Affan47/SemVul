onCmdAbout(FXObject*,FXSelector,void*){
  FXMessageBox about(this,"About Bitmap Viewer","Bitmap Viewer demonstrates the FOX Bitmapview widget.\n\nUsing the FOX C++ GUI Library (http://www.fox-toolkit.org)\n\nCopyright (C) 2003,2004 Jeroen van der Zijp (jeroen@fox-toolkit.org)",NULL,MBOX_OK|DECOR_TITLE|DECOR_BORDER);
  about.execute();
  return 1;
  }
