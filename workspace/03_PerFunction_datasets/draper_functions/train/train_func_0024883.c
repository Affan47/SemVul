Unexecute () {
    GetEditor()->GetComponent()->Uninterpret(this);
    Clipboard* cb = GetClipboard();
    Iterator i;
    for (cb->First(i); !cb->Done(i); cb->Next(i)) {
        GraphicComp* gcomp = cb->GetComp(i);
        if (gcomp->IsA(EDGE_COMP)) {
	    EdgeComp* comp = (EdgeComp*)gcomp;
            NodeComp* start = node(cb, comp->GetStartNode());
   	    NodeComp* end = node(cb, comp->GetEndNode());
            EdgeConnectCmd* cmd = new EdgeConnectCmd(GetEditor(), comp, start, end);
	    cmd->Execute();
	    delete cmd;
        }
    }
    _executed = false;
}
