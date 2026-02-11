resize(int w, int h)
{
	if (w == bufW && h == bufH)
		return;

	gContainer::resize(w, h);


	updateSize();


}
