file_dialog_open()
{
  const int FILE_DIALOG_MAX_BUFFER = 1024;
  char buffer[FILE_DIALOG_MAX_BUFFER];

#ifdef __APPLE__

  FILE * output = popen(
    "osascript -e \""
    "   tell application \\\"System Events\\\"\n"
    "           activate\n"
    "           set existing_file to choose file\n"
    "   end tell\n"
    "   set existing_file_path to (POSIX path of (existing_file))\n"
    "\" 2>/dev/null | tr -d '\n' ","r");
  while ( fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL )
  {
  }
#elif defined _WIN32


  OPENFILENAME ofn;
  char szFile[260];


  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.hwndOwner = NULL;
  ofn.lpstrFile = new char[100];


  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = "*.*\0";
  ofn.nFilterIndex = 1;
  ofn.lpstrFileTitle = NULL;
  ofn.nMaxFileTitle = 0;
  ofn.lpstrInitialDir = NULL;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


  int pos = 0;
  if (GetOpenFileName(&ofn)==TRUE)
  {
    while(ofn.lpstrFile[pos] != '\0')
    {
      buffer[pos] = (char)ofn.lpstrFile[pos];
      pos++;
    }
    buffer[pos] = 0;
  }

#else


  FILE * output = popen("/usr/bin/zenity --file-selection","r");
  while ( fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL )
  {
  }

  if (strlen(buffer) > 0)
  {
    buffer[strlen(buffer)-1] = 0;
  }
#endif
  return std::string(buffer);
}
