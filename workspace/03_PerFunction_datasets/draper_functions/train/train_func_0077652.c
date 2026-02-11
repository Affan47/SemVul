set_timesync_reference(QAction *action)
{
  int i;

  for(i=0; i<files_open; i++)
  {
    if(!strcmp(edfheaderlist[i]->filename, action->text().toLocal8Bit().data()))
    {
      break;
    }
  }

  sel_viewtime = i;

  setMainwindowTitle(edfheaderlist[sel_viewtime]);

  setup_viewbuf();
}
