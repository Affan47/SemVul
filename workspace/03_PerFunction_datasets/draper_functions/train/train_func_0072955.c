add(const LineString *line)
{

	if (graph==NULL)
		graph=new PolygonizeGraph(line->getFactory());
	graph->addEdge(line);
}
