X11EndPage(DISPLAY * ipsDisplay)
{


	while (textRow <= rows)
	{
		StoreEndOfLine(textRow, textCol);
		textCol = 0;
		textRow++;
	}


	UpdateWindow();
	XFlush(display);
}
