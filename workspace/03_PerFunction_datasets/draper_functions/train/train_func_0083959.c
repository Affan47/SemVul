addSmapFolderCmd(mail::smapAddMessage *add,
				  std::string path)
{
	vector<string> words;
	smapHandler::path2words(path, words);

	vector<string>::iterator b, e;

	string pstr="ADD FOLDER ";

	b=words.begin();
	e=words.end();

	while (b != e)
	{
		pstr += " ";
		pstr += quoteSMAP( *b );
		b++;
	}

	pstr += " \"\"\n";

	add->cmds.push_back(pstr);
}
