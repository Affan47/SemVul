CGUISpriteBank(IGUIEnvironment* env) :
	Environment(env), Driver(0)
{
	#ifdef _DEBUG
	setDebugName("CGUISpriteBank");
	#endif

	if (Environment)
	{
		Driver = Environment->getVideoDriver();
		if (Driver)
			Driver->grab();
	}
}
