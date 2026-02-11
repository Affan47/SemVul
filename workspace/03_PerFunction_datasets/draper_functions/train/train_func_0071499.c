map(const QPen& pen) const
{
	QPen result(pen);
	result.setBrush(map(pen.brush()));
	return result;
}
