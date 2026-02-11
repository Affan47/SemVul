CreateRegularPrism(uint32_t numBaseEdges,double baseRadius,double height)	{
	return CreateCustomPrism(generateBase(numBaseEdges,baseRadius),height);
}
