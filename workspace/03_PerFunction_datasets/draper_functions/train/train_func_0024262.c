clearScreenFrames(void)
{
	UT_sint32 i =0;
	for (i = 0; i < countAboveFrameContainers(); i++)
	{
		getNthAboveFrameContainer(i)->clearScreen();
	}
	for (i = 0; i < countBelowFrameContainers(); i++)
	{
		getNthBelowFrameContainer(i)->clearScreen();
	}
}
