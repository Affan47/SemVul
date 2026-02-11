updateGenre(TextIdentificationFrame *frame) const
{
  StringList fields = frame->fieldList();
  StringList newfields;

  for(StringList::Iterator it = fields.begin(); it != fields.end(); ++it) {
    String s = *it;
    int end = s.find(")");

    if(s.startsWith("(") && end > 0) {

      String text = s.substr(end + 1);
      bool ok;
      int number = s.substr(1, end - 1).toInt(&ok);
      if(ok && number >= 0 && number <= 255 && !(ID3v1::genre(number) == text))
        newfields.append(s.substr(1, end - 1));
      if(!text.isEmpty())
        newfields.append(text);
    }
    else {

      newfields.append(s);
    }
  }

  if(newfields.isEmpty())
    fields.append(String::null);

  frame->setText(newfields);

}
