addLine(const LineString *lineString)
{
	if (factory == NULL) {
		factory = lineString->getFactory();
	}
	graph.addEdge(lineString);
	++lineCount;
}
