Highlight_file(short index)
{

  if ((Filelist.Nb_elements<=10) || (index<5))
  {
    Main_fileselector_position=0;
    Main_fileselector_offset=index;
  }
  else
  {
    if (index>=Filelist.Nb_elements-5)
    {
      Main_fileselector_position=Filelist.Nb_elements-10;
      Main_fileselector_offset=index-Main_fileselector_position;
    }
    else
    {
      Main_fileselector_position=index-4;
      Main_fileselector_offset=4;
    }
  }
}
