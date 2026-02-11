additionalVertices(JohnsonBodyPart j,uint32_t numBaseEdges)	{
	if (j==INF_NO_BODY||j==SUP_NO_BODY) return 0;
	else if (j<UPWARDS_CUPOLA) return 1;
	else if (j<PRISM) return numBaseEdges>>1;
	else if (j<UPWARDS_ROTUNDA) return numBaseEdges;
	else return 10;
}
