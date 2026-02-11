drawConnector(QPainter & painter, Region region, unsigned index)
{
	switch (region)
	{
	case inportsRegion:
		painter.drawEllipse(
				0, portOffset+index*portStep,
			   	portWidth, portHeight);
	return;
	case outportsRegion:
		painter.drawEllipse(
				_size.width()-portWidth, portOffset+index*portStep,
			   	portWidth, portHeight);
	return;
	case incontrolsRegion:
		painter.drawRect(
				controlOffset+index*controlStep, 0,
			   	controlWidth, controlHeight);
	return;
	case outcontrolsRegion:
		painter.drawRect(
				controlOffset+index*controlStep, _size.height()-controlHeight,
			   	controlWidth, controlHeight);
	return;
	default:
	return;
	}
}
