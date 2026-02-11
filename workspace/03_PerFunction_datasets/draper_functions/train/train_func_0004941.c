colummTransposition(string cypherText, string plainWords)
{
  vector<int> key;
  string text[8];
  int index=0;

  stringstream ss (plainWords);

  vector<string> word;
  string tmp;

  while(ss >> tmp) word.push_back(tmp);

  for(unsigned int i=0; i<cypherText.size(); i++, index = (index+1)%8)
    text[index].append(1, cypherText[i]);

  unsigned int sizeColumn = text[0].size();

  for(int i=0; i<8; i++)
  {
    if(text[i].size() < sizeColumn)
      text[i].append(1, ' ');
  }

  string plainText = "";
  int possibleKey[] = {0,1,2,3,4,5,6,7};

  do
  {
    plainText.clear();

    bool isEnd = true;

    for(unsigned int i=0; i<sizeColumn; i++)
    {
      for(unsigned int j=0; j<8; j++)
        plainText.append(1, text[possibleKey[j]][i]);
    }

    for(unsigned int i=0; i<word.size(); i++)
    {
      if(plainText.find(word[i]) == string::npos)
      {
        isEnd = false;
        break;
      }
    }

    if(isEnd) break;

  } while(next_permutation(possibleKey, possibleKey+8));

  writeToFile(plainText, possibleKey, -1);

  return plainText;
}
