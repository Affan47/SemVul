getNumberWords (const string& text) const
{
  int count = 0;
  string line = trimStr(text);
  if (line.length()>0) {
    int pos = line.find(" ");
    while (pos!=int(string::npos)) {
      count++;
      pos = line.find(" ",pos+1);
    }
    count++;
  }
  return count;
}
