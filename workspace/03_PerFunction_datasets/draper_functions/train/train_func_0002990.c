bufferOp(const Geometry *g, double distance,
		int quadrantSegments,
		int nEndCapStyle)
{
	BufferOp bufOp(g);
	bufOp.setQuadrantSegments(quadrantSegments);
	bufOp.setEndCapStyle(nEndCapStyle);
	return bufOp.getResultGeometry(distance);
}
