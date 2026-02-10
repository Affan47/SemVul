StartButtonInit(int height)
{
  FvwmPicture *p = NULL;
  int pw;
  FvwmPictureAttributes fpa;
  StartAndLaunchButtonItem *tempPtr;

  fpa.mask = FPAM_NO_ALLOC_PIXELS;


  if (First_Start_Button == NULL && !NoDefaultStartButton)
  {
    StartButtonParseConfig("*FvwmTaskBarStartName Start");
    StartButtonParseConfig("*FvwmTaskBarStartMenu RootMenu");
    StartButtonParseConfig("*FvwmTaskBarStartIcon mini.start.xpm");
  }

  if (First_Start_Button && First_Start_Button->isStartButton == True)
  {
    if (First_Start_Button->buttonCaption == NULL)
      UpdateString(&(First_Start_Button->buttonCaption), "Start");
    if (First_Start_Button->buttonIconFileName == NULL)
      UpdateString(&(First_Start_Button->buttonIconFileName), "mini-start.xpm");
  }

  tempPtr = First_Start_Button;

  while(tempPtr != NULL)
  {
	  p = PGetFvwmPicture(
		  dpy, win, ImagePath, tempPtr->buttonIconFileName, fpa);
	  if (p != NULL && strlen(tempPtr->buttonCaption) != 0)
	  {

		  pw = p->width + 12;
	  }
	  else if (p != NULL)
	  {

		  pw = p->width + 8;
	  }
	  else
	  {

		  pw = 10;
	  }

    tempPtr->buttonItem = (Button *)ButtonNew(
	    tempPtr->buttonCaption, p, BUTTON_UP,0);
    if (tempPtr->isStartButton)
    {
	    StartButton = tempPtr->buttonItem;
	    tempPtr->width = FlocaleTextWidth(
		    FSelButtonFont, tempPtr->buttonCaption,
		    strlen(tempPtr->buttonCaption)) + pw;
    }
    else
    {
	    tempPtr->width = FlocaleTextWidth(
		    FButtonFont, tempPtr->buttonCaption,
		    strlen(tempPtr->buttonCaption)) + pw;
    }
    tempPtr->height = height;
    StartAndLaunchButtonsWidth += tempPtr->width;
    tempPtr=tempPtr->tail;
    PFreeFvwmPictureData(p);
  }
  if (First_Start_Button)
  {
	  StartAndLaunchButtonsWidth += StartButtonRightMargin;
	  First_Start_Button->height = height;
	  StartAndLaunchButtonsHeight = First_Start_Button->height;
  }
  else
  {
    StartAndLaunchButtonsWidth = 0;
    StartButtonRightMargin = 0;
    if (has_wb_left_margin == 0)
    {
      WindowButtonsLeftMargin = 0;
    }
    if (has_wb_right_margin == 0)
    {
      WindowButtonsRightMargin = 0;
    }
  }
}
