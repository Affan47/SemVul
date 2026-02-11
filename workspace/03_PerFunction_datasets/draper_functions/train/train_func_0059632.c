release(int button, int unicode)
{
	if(top)
	{
		top->unicode = unicode;
		top->release(button);
	}
}
