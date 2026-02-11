resize(int w, int h)
{
	if (w == bufW && h == bufH)
		return;

	_client_w = 0;
	_client_h = 0;

	gControl::resize(w, h);
	performArrange();
}
