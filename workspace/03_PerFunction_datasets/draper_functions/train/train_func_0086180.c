CheckForHangon(unsigned long *body)
{
  int button,i,j;
  char *cbody;

  cbody = (char *)&body[3];
  for(i=0;i<num_rows;i++)
    for(j=0;j<num_columns; j++)
      {
	button = i*num_columns + j;
	if(Buttons[button].hangon != NULL)
	  {
	    if(strcmp(cbody,Buttons[button].hangon)==0)
	      {
		if(Buttons[button].swallow ==  1)
		  {
		    Buttons[button].swallow = 2;
		    if(Buttons[button].IconWin != None)
		      {
			XDestroyWindow(dpy,Buttons[button].IconWin);
		      }
		    Buttons[button].IconWin = (Window)body[0];
		    free(Buttons[button].hangon);
		    Buttons[button].hangon = NULL;
		  }
		else
		  {
		    Buttons[button].up = 1;
		    free(Buttons[button].hangon);
		    Buttons[button].hangon = NULL;
		    RedrawWindow(button);
		  }
	      }
	  }
      }
}
