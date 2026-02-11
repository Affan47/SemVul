getLowestUtilzedPortToLid(IBNode *p_node, unsigned int dLid)
{
    IBPort *p_port;
    int minUtil;
    int minUtilPortNum = 0;


    int minHop = p_node->getHops(NULL,dLid);

    for (unsigned int pn = 1; pn <= p_node->numPorts; pn++) {
        p_port = p_node->getPort(pn);

        if (! p_port)
            continue;
        if (! p_port->p_remotePort)
            continue;


        if (p_node->getHops(p_port, dLid) == minHop) {
            if ((minUtilPortNum == 0) || (p_port->counter1 < minUtil)) {
                minUtilPortNum = pn;
                minUtil = p_port->counter1;
            }
        }
    }
    return( minUtilPortNum );
}
