saveUserSettingsFile(char* filename)
{
  Parameter* us = getParameter(0, ECIF_USER_SETTING);

  if (us == NULL) {
    return;
  }

  ofstream out(filename, ios::out);

  char time_buffer[80];
  getCurrentTime(time_buffer);

  out << "!Elmer Cadi default user settings" << endl;
  out << "!" << time_buffer << endl;
  out << endl;


  SifOutputControl soc;
  soc.outputId = false;
  soc.outputAll = true;

  us->output_sif(out, 2, 0, soc);

  out << "End" << endl;

  out.close();
}
