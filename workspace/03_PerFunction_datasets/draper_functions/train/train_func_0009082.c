setSampledExtra()
{


    if (_data_gen) {


	return;
    }


    Graph egraph;
    for (set<Node *>::const_iterator p = _extra_nodes.begin();
	 p != _extra_nodes.end(); ++p)
    {
	egraph.add(*p);
    }

    GraphMarks emarks(egraph);
    for (list<MonitorControl>::const_iterator p = _monitors.begin();
	 p != _monitors.end(); ++p)
    {
	for (unsigned int i = 0; i < p->monitor()->nodes().size(); ++i) {
	    Node const *node = p->monitor()->nodes()[i];
	    if (egraph.contains(node)) {
		emarks.mark(node, 1);

		emarks.markAncestors(vector<Node const *>(1, node), 1);
	    }
	}
    }

    for (set<Node *>::const_iterator p = _extra_nodes.begin();
	 p != _extra_nodes.end(); ++p)
    {
	if (emarks.mark(*p) == 0)
	    egraph.remove(*p);
    }

    _sampled_extra.clear();
    egraph.getSortedNodes(_sampled_extra);
}
