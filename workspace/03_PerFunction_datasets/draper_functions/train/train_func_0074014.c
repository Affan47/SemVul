getEnabledActions(vector<string>& statev) {
    vector<string> enabled;
    BDD state = globalStateName2BDD(statev);

    BDD outActions = (state * transition).ExistAbstract(globalStatesCube * globalStatesPrimedCube);

    if(outActions != manager.bddZero()) {

        for(set<string>::const_iterator it = actions.begin(); it != actions.end(); ++it) {
            if(outActions.ExistAbstract(getActionBDD(*it)) != outActions) {
                enabled.push_back(*it);
                }
            }

        }

    return enabled;
    }
