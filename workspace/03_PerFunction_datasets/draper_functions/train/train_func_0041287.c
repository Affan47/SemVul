pushRequests(vec_int req)
{
  if (FabricUtilsVerboseLevel & FABU_LOG_VERBOSE)
    cout << "-V- Pushing requests" << endl;

  for (int i=0; i<req.size(); i++) {

    int src = i;
    int dst = req[i];

    if (FabricUtilsVerboseLevel & FABU_LOG_VERBOSE)
      cout << "-V- Req: " << src << "->" << dst << endl;


    if ((src >= ports) || (dst >= ports)) {
      cout << "-E- Port index exceeds num ports! Ports: " << ports << ", src: " << src << ", dst: " << dst << endl;
      return 1;
    }

    if (inPorts[src].used || outPorts[dst]) {
      cout << "-E- Port already used! src: " << src << ", dst: " << dst << endl;
      return 1;
    }

    inPorts[src].used = true;
    inPorts[src].src = src;
    inPorts[src].dst = dst;
    inPorts[src].inputNum = src;
    inPorts[src].outNum = dst;

    outPorts[dst] = true;
  }
  return 0;
}
