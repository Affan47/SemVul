valuation2BDD(map<string, vector<string> > valuation) {

    BDD result = manager.bddOne();
    for(set<string>::const_iterator it = parVars.begin(); it != parVars.end(); ++it) {
        string varname = *it;
        if(valuation[varname].size() == 0) {
            cerr << "Panic: valuation can't be empty! (it was for " << varname << ")" << endl;
            exit(1);
            }
        for(set<string>::const_iterator ii = actions.begin(); ii != actions.end(); ++ii) {
            string action = *ii;
            BDD actionBDD = getActionBDD(action, varname);

            if(find(valuation[varname].begin(), valuation[varname].end(), action) != valuation[varname].end()) {
                result *= actionBDD;
                }
            else result *= !actionBDD;
            }
        }

    return result;
    }
