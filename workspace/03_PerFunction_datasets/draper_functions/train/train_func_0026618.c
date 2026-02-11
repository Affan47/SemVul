opacityCloseUpdate()
{
	if(mOpacity > 0.0f)
	{
		mOpacity -= 0.06f;
		setWindowOpacity(mOpacity);
	}
	else
		QApplication::quit();
}
