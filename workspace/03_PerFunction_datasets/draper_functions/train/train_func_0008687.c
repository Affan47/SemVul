SubnMgtFindTreeRootNodes(IBFabric *p_fabric)
{
    list_pnode nextNodes;
    list_pnode curNodes;
    list_pnode rootNodes;
    list_pnode emptyRes;
    IBNode *p_node;
    int rank = 0;
    map_pnode_int nodeRankMap;

    cout << "-I- Automatically recognizing the tree root nodes ..."
            <<  endl;


    for( map_str_pnode::iterator nI = p_fabric->NodeByName.begin();
            nI != p_fabric->NodeByName.end();
            nI++) {
        p_node = (*nI).second;
        if (p_node->type == IB_SW_NODE)
            continue;

        curNodes.push_back(p_node);
    }


    while (! curNodes.empty()) {
        rank++;
        nextNodes.clear();


        rootNodes = curNodes;

        if (0) {
            cout << "-V- Level:" << rank << " nodes:" << endl;
            int nInLine = 1;
            for (list_pnode::iterator nI = curNodes.begin();
                    nI != curNodes.end();
                    nI++) {
                if (nInLine == 16) {
                    nInLine = 0;
                    cout << endl;
                }
                nInLine++;
                cout << (*nI)->name << " ";
            }
        }


        while (! curNodes.empty()) {
            p_node = curNodes.front();
            curNodes.pop_front();


            for (unsigned int pn = 1; pn <= p_node->numPorts; pn++) {
                IBPort *p_port = p_node->getPort(pn);


                if (p_port && p_port->p_remotePort) {
                    IBNode *p_remNode = p_port->p_remotePort->p_node;


                    if (p_remNode->type != IB_SW_NODE)
                        continue;


                    map_pnode_int::iterator nI = nodeRankMap.find(p_remNode);
                    if (nI != nodeRankMap.end()) {
                        int remNodeRank = (*nI).second;


                        if ((remNodeRank != rank + 1) && (remNodeRank != rank - 1)) {
                            cout << "-E- Given topology is not a pure levelized tree:" << endl;
                            cout << "    Node:" << p_remNode->name << " rank:" << remNodeRank
                                    << " accessed from node:" << p_node->name
                                    << " rank:" << rank << endl;
                            return emptyRes;
                        }
                    } else {

                        nodeRankMap[p_remNode] = rank + 1;


                        nextNodes.push_back(p_remNode);
                    }
                }
            }
        }
        curNodes = nextNodes;
    }
    return rootNodes;
}
