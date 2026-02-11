ParseMetapostWord(unsigned int pos, Accessor &styler, char *word)
{
  int length=0;
  char ch=styler.SafeGetCharAt(pos);
  *word=0;

  while(isMETAPOSTidentifier(ch) && isalpha(ch) && length<100){
          word[length]=ch;
          length++;
          ch=styler.SafeGetCharAt(pos+length);
  }
  word[length]=0;
  return length;
}
