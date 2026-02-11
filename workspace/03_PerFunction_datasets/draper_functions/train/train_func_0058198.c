endLineField()
{
  if (inlineState_ == inlineFieldEnd) {
    osp_ = &tempos_;


    String<char> str;
    fieldos_.extractString(str);
    size_t i = str.size();
    for (; i > 0; i--)
      if (str[i - 1] != ' ')
        break;

    int sep = (str.size() - i)*outputFormat_.fontSize*5/2;
    str.resize(i);
    static const int minTabSep = 26;
    if (sep < minTabSep)
      sep = minTabSep;
    os() << "\\tqr\\tx" <<  fieldTabPos_ - sep << "\\tx" << fieldTabPos_ << "\\tab ";
    os() << str;
    os() << "\\tab ";
  }
  else if (inlineState_ == inlineField) {
    os() << "\\tab ";
    inlineState_ = inlineMiddle;
  }
  end();
}
