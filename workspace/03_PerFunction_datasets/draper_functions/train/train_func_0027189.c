iluCrop(ILuint XOff, ILuint YOff, ILuint ZOff, ILuint Width, ILuint Height, ILuint Depth)
{
	if (ZOff <= 1)
		return iluCrop2D(XOff, YOff, Width, Height);
	return iluCrop3D(XOff, YOff, ZOff, Width, Height, Depth);
}
