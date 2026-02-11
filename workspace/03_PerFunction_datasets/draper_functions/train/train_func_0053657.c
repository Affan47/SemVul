optimizeScope(const string& srcString)
{
	string wxcurrScope;
	std::vector<std::string> scope_stack;
	std::string currScope;

	int type;


	const char * scannerText =  srcString.c_str ();
	_extra_tokenizer->setText (scannerText);
	bool changedLine = false;
	bool prepLine = false;
	int curline = 0;
	while (true)
	{
		type = _extra_tokenizer->yylex();


		if (type == 0)
		{
			if (!currScope.empty())
				scope_stack.push_back(currScope);
			break;
		}


		if ( prepLine && _extra_tokenizer->lineno() == curline)
		{
			currScope += " ";
			currScope += _extra_tokenizer->YYText();
			continue;
		}

		prepLine = false;


		changedLine = (_extra_tokenizer->lineno() > curline);
		if (changedLine)
		{
			currScope += "\n";
		}

		curline = _extra_tokenizer->lineno();
		switch (type)
		{
		case (int)'(':
			currScope += "\n";
			scope_stack.push_back(currScope);
			currScope = "(\n";
			break;
		case (int)'{':
			currScope += "\n";
			scope_stack.push_back(currScope);
			currScope = "{\n";
			break;
		case (int)')':

			if ( !scope_stack.empty() ) {
				currScope = scope_stack.back();
				scope_stack.pop_back();
				currScope += "()";
			} else
				currScope.clear();
			break;
		case (int)'}':

			if ( !scope_stack.empty() ) {
				currScope = scope_stack.back();
				scope_stack.pop_back();
				currScope += "\n{}\n";
			} else {
				currScope.clear();
			}
			break;
		case (int)'#':
			if (changedLine) {


				currScope += " ";
				currScope += _extra_tokenizer->YYText();
				prepLine = true;
				break;
			}
		default:
			currScope += " ";
			currScope += _extra_tokenizer->YYText();
			break;
		}
	}

	_extra_tokenizer->reset();

	if (scope_stack.empty())
		return srcString;

	currScope.clear();
	size_t i = 0;
	for (; i < scope_stack.size(); i++)
		currScope += scope_stack.at(i);


	if ( currScope.empty() == false ) {
		currScope += ";";
		return currScope.c_str();
	}

	return srcString;
}
