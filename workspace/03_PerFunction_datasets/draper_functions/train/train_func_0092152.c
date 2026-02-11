highlightColor(unsigned long hlc_)
{
  if (buttons().length()>0)
    {
      if (highlightColor()!=hlc_)
	{
	  AplusActionButton *btn;
	  unsigned numButtons=buttons().length();

	  for (int i=0; i<numButtons; i++)
	    {
	      btn=(AplusActionButton *)(MSWidget *)buttons()(i);
	      if (btn)
		btn->highlightColor(hlc_);
	    }
	}
    }

  MSActionBox::highlightColor(hlc_);
}
