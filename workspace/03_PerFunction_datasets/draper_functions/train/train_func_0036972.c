PrintColumn(std::ostream& os,
                                               const char* text)
{

  const char* l = text;
  long column = 0;
  bool newSentence = false;
  bool firstLine = true;
  int width = this->TextWidth - static_cast<int>(strlen(this->TextIndent));


  while(*l)
    {

    const char* r = l;
    while(*r && (*r != '\n') && (*r != ' ')) { ++r; }


    if(r-l < (width-column-(newSentence?1:0)))
      {

      if(r > l)
        {
        if(column)
          {


          if(newSentence)
            {
            os << "  ";
            column += 2;
            }
          else
            {
            os << " ";
            column += 1;
            }
          }
        else
          {


          os << (firstLine?"":this->TextIndent);
          }


        os.write(l, static_cast<long>(r-l));
        newSentence = (*(r-1) == '.');
        }

      if(*r == '\n')
        {

        os << "\n";
        ++r;
        column = 0;
        firstLine = false;
        }
      else
        {

        column += static_cast<long>(r-l);
        }
      }
    else
      {

      os << "\n";
      firstLine = false;
      if(r > l)
        {
        os << this->TextIndent;
        os.write(l, static_cast<long>(r-l));
        column = static_cast<long>(r-l);
        newSentence = (*(r-1) == '.');
        }
      else
        {
        column = 0;
        }
      }


    l = r;
    while(*l && (*l == ' ')) { ++l; }
    }
}
