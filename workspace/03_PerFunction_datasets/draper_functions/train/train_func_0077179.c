CreateAnimated()
{
	float* values[3] = { &value.x, &value.y, &value.z };
	return new FCDAnimated((FCDObject*) GetParent(), 3, FCDAnimatedStandardQualifiers::RGBA, values);
}
