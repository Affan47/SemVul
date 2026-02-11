check_EX(set<string> actions, BDD pstates) {
    BDD swpstates = pstates.SwapVariables(net.allStateBDDVars, net.allStateBDDVarsPrimed);
    BDD result = net.getLabeledTransitions(actions) * swpstates;
    result = result.ExistAbstract(net.globalStatesPrimedCube);

    return result * net.statespace;
    }
