convert_startend_to_iob2_sub(vector<string> & s)
{
  for (int i = 0; i < s.size(); i++) {
    string tag = s[i];
    string newtag = tag;
    if (tag[0] == 'S') {
      newtag = "B" + tag.substr(1);
    }
    if (tag[0] == 'E') {
      newtag = "I" + tag.substr(1);
    }
    s[i] = newtag;
  }
}
