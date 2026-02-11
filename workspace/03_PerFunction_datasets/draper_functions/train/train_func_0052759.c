computeDirectedLabel()
{
	label = edge->getLabel();
	if (!isForwardVar)
		label.flip();
}
