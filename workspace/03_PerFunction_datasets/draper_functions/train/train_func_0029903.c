recursiveStatesDescription(BDD& globalsSet, vector< vector<string> >& knownLocals,
        unsigned int position, vector<string> currstring,
        vector< vector<string> >& goodLocalStates) {
    if(position >= knownLocals.size()) {

        BDD currentState = manager.bddOne();
        for(unsigned int i = 0; i < currstring.size(); ++i) {
            currentState *= components[i]->getStateBDD(currstring[i]);
            }
        if(currentState * globalsSet == currentState ) goodLocalStates.push_back(currstring);
        }
    else {
        for(unsigned int i = 0; i < knownLocals[position].size(); ++i) {
            vector<string> loc = currstring;
            loc.push_back(knownLocals[position][i]);
            recursiveStatesDescription(globalsSet, knownLocals, position + 1, loc, goodLocalStates);
            }
        }
    }
