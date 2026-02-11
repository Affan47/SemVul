main()
{
  ifstream numstream("problem13.txt");

  int carry = 0;

  stringstream intString;
  string sum;

  string line;


  line.reserve(50);

  for(int i = 49; i >= 0; i--)
  {

    getline(numstream, line);

    while(!numstream.eof())
    {

      carry += (line[i] - '0');
      getline(numstream, line);
    }

    if(i == 0)
    {
      intString << carry;
    }
    else
    {
      intString << carry%10;
      carry /= 10;
    }

    sum = intString.str() + sum;


    intString.str(string());


    numstream.clear();
    numstream.seekg(0, ios::beg);
  }

  numstream.close();


  cout << sum.substr(0, 10);

  return 0;
}
