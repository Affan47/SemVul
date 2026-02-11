globalStateSetDescription(BDD globalsSet) {


    vector< vector<string> > knownLocalStates(components.size());
    vector< vector<string> > goodLocalStates;

    for(unsigned int i = 0; i < components.size(); ++i) {
        for(stringToBDD::const_iterator stiter = components[i]->state2encoding.begin();
                stiter != components[i]->state2encoding.end(); ++stiter) {
            string state = stiter->first;
            BDD encoding = stiter->second;

            if(encoding * globalsSet != manager.bddZero()) knownLocalStates[i].push_back(state);
            }
        }


    vector<string> helper;
    recursiveStatesDescription(globalsSet, knownLocalStates, 0, helper, goodLocalStates);

    return goodLocalStates;
    }
