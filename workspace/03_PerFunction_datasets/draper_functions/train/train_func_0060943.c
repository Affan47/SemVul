RedrawUnpushed(Window *win, int i, int j)
{
  if (PushStyle!=0) {
    XMoveResizeWindow(dpy, Buttons[CurrentButton].IconWin,
		      (j-1)*BUTTONWIDTH ,(i-1)*BUTTONHEIGHT,
		      BUTTONWIDTH, BUTTONHEIGHT);
  } else {
    XCopyArea( dpy, Buttons[CurrentButton].completeIcon,
	       Buttons[CurrentButton].IconWin, NormalGC, 0, 0,
	       Buttons[BACK_BUTTON].icons[0].w,
	       Buttons[BACK_BUTTON].icons[0].h,
	       0,0);
  }
  RedrawWindow(win,0, CurrentButton, num_rows, num_columns);

  RedrawUnpushedOutline(win, i, j);
}
