DetPlaceNetCost()
{
    double NetCost = 0.0;

    vector<PONet*>::iterator nfirst = _nets.begin();
    vector<PONet*>::iterator nlast  = _nets.end();
    while (nfirst != nlast) {
	PONet& net = **nfirst++;
	PBBox& bbox = net.CurrentBBox();
	vector<PElem*>::iterator ifirst = net.GetElems().begin();
	vector<PElem*>::iterator ilast  = net.GetElems().end();
	while (ifirst != ilast)
	    bbox.Merge((*ifirst++)->GetPos());

	NetCost += bbox.GetHeight() + bbox.GetWidth();
    }
    return NetCost;
}
