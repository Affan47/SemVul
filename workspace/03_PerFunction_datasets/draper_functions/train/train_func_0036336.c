internalBuildChoices(
	std::map<std::string, double> *choices, std::string *str,
	std::list<std::string> *choicesList)
{
  std::map<std::string, double>::iterator it;
  bool first;
  std::string choiceStr;

  for (it = choices->begin(), first = true; it != choices->end(); it++)
  {
    choiceStr = (*it).first;
    choicesList->push_back(choiceStr);
    if (!first)
      (*str) += "|";
    first = false;
    (*str) += choiceStr;
  }
}
