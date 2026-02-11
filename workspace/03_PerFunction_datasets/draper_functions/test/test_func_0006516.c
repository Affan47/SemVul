alphabetic(string cypherText, string key)
{
  int length=0;

  for(unsigned int i=0; i<key.size(); i++)
		length = (length + key[i]) % cypherText.size();

  for(unsigned int i=0; i<cypherText.size(); i++)
  {
    for(int j=0; j<length; j++)
    {
      if(cypherText[i] == '0')
      {
        cypherText[i] = 32;
        continue;
      }
      else if(cypherText[i] == 'A')
      {
        cypherText[i] = '9';
        continue;
      }
      else if(cypherText[i] == 'a')
      {
        cypherText[i] = 'Z';
        continue;
      }
      else if(cypherText[i] == 32)
      {
        cypherText[i] = 'z';
        continue;
      }

      cypherText[i]--;
    }
  }

  return cypherText;
}
