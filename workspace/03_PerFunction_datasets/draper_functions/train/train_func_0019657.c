setState(BallState newState)
{
	state = newState;
	if (state == Holed || !EllipticalCanvasItem::isVisible())
		setSimulationType(CanvasItem::NoSimulation);
	else
		setSimulationType(CanvasItem::DynamicSimulation);

	if (state != Stopped)
		setBeginningOfHole(false);
}
