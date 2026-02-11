onMouseButtonUp(MouseEventArgs& e)
{

	Window::onMouseButtonUp(e);

	if (e.button == LeftButton && isCapturedByThis())
	{

		releaseInput();
		++e.handled;
	}

}
