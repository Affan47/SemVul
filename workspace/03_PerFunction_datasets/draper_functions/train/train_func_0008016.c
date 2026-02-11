getVariableNames(ParseTree const *ptree, set<string> &names,
			     vector<string> &counterstack)
{


    if (ptree->treeClass() == P_VAR) {
	bool is_counter = false;
	for (unsigned int i = 0; i < counterstack.size(); ++i) {
	    if (ptree->name() == counterstack[i]) {
		is_counter = true;
		break;
	    }
	}
	if (!is_counter) {
	    names.insert(ptree->name());
	}
    }

    vector<ParseTree*> const &param = ptree->parameters();
    for (vector<ParseTree*>::const_iterator p = param.begin();
	 p != param.end(); ++p)
    {
	ParseTree *counter;

	if (*p) {

	    switch ((*p)->treeClass()) {
	    case P_FOR:
		counter = (*p)->parameters()[0];
                for (unsigned int i = 0; i < counter->parameters().size(); ++i)
                {
                    getVariableNames(counter->parameters()[i], names,
                                     counterstack);
                }
		counterstack.push_back(counter->name());
		getVariableNames((*p)->parameters()[1], names, counterstack);
		counterstack.pop_back();
		break;
	    default:
		getVariableNames(*p, names, counterstack);
		break;
	    }
	}
    }
}
