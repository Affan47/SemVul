main(int argc, char *argv[])
{

	string name = argv[0];

	if(argc != 4)
	{
		cout << "Try to type :"<< endl
				 << " ./decypher <cypherText> <key> <mode>" << endl
				 << " Mode = ('-sub') | ('-tran') | ('-all')"<<endl;
		exit(-1);
	}

  Decryption decryption;
  string cypherText, key, plainText;

  cypherText = readFile(argv[1]);
  cout << cypherText << endl;

  key = readFile(argv[2]);
  cout << key << endl;

  string mode = argv[3];

  if(mode == "-sub")
    plainText = decryption.decrypt(cypherText, key, SUBSTITUTION);

  else if(mode == "-tran")
    plainText= decryption.decrypt(cypherText ,key, TRANSPOSITION);

  else if(mode == "-all")
	{
    plainText= decryption.decrypt(cypherText ,key, PRODUCT);
	}
	else
  {
    cout << "invalid comand" << endl;
    exit(-1);
  }

  cout <<"["<<plainText<<"]"<< endl;

	writeToFile(plainText);

	return 0;
}
