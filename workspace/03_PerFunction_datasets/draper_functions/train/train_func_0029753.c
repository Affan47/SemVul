index_clipboard(Selection* s, Clipboard* cb) {
    Iterator i, j;
    cb->First(j);
    for (s->First(i); !s->Done(i); s->Next(i)) {
        GraphicComp* gcomp = s->GetView(i)->GetGraphicComp();
        if (gcomp->IsA(EDGE_COMP)) {
            GraphicComp* cbgcomp = cb->GetComp(j);
	    EdgeComp* comp = (EdgeComp*)gcomp;
            TopoEdge* topoedge = comp->Edge();
            int start = -1;
            int end = -1;
            if ((topoedge->start_node()) && selected(s,  comp->NodeStart()))
	        start = node_index(s, comp->NodeStart());
            if ((topoedge->end_node()) && selected(s, comp->NodeEnd()))
	        end = node_index(s, comp->NodeEnd());

	    EdgeComp* cbcomp = (EdgeComp*)cbgcomp;
	    cbcomp->SetStartNode(start);
	    cbcomp->SetEndNode(end);
        }
        cb->Next(j);
    }
}
