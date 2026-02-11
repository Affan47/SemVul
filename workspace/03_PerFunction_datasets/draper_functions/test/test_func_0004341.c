endif()
{

	if (Scopes.size() > 0)
	{
		Scopes.pop_back();
		if (Scopes.size() == 0)
			Current = Main;
		else
			Current = Scopes[Scopes.size()-1]->getLastScope();
	}
	else
		std::cerr << ResolvedName << ": Too much endifs for me" << std::endl;
}
