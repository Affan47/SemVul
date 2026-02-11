handleArgumentInfo() {

  unsigned savedArgsLength;
  if( fread(&savedArgsLength, sizeof(unsigned), 1, _file) != 1 ) {
    errs() << "warning: argument info header/data mismatch\n";
    return;
  }


  char* args = new char[savedArgsLength+1];
  if( fread(args, 1, savedArgsLength, _file) != savedArgsLength )
    errs() << "warning: argument info header/data mismatch\n";

  args[savedArgsLength] = '\0';
  argList = std::string(args);
  delete [] args;


  if (savedArgsLength & 3)
    fseek(_file, 4-(savedArgsLength&3), SEEK_CUR);
}
