configureButtonOption(char* button, char* option, char* value)
{
  ostrstream strm;
  strm << button << tclArgSeparator
       << option << tclArgSeparator
       << value << ends;

  sendCommandToGui(theInterp, "Interface::configureButtonOption", strm.str());
}
