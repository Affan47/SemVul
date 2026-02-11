hasSequence(planargraph::Subgraph& graph)
{
	int oddDegreeCount = 0;
	for (planargraph::NodeMap::container::const_iterator
		it=graph.nodeBegin(), endIt=graph.nodeEnd();
		it!=endIt;
		++it)
	{
		planargraph::Node* node = it->second;
		if (node->getDegree() % 2 == 1)
		oddDegreeCount++;
	}
	return oddDegreeCount <= 2;
}
