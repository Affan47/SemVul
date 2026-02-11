is_marker(char *string) {
  int i;
  int length = strlen(string);
  for(i = 0; i < length; i++) {

    if(i < (length - 1)) {
      if(!isalnum(string[i])) {
        return false;
      }
    } else {
      if(string[i] == ':') {
        return true;
      }
    }
  }
  return false;
}
