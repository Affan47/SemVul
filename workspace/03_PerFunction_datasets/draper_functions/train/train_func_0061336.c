warning(const std::string & message)
    {
	if(at_once > 0)
	{
 	    U_I c = 0, max = message.size();
	    while(c < max)
	    {
		if(message[c] == '\n')
		    count++;
		c++;
	    }
	    count++;
	    if(count >= at_once)
	    {
		count = 0;
		(void)this->pause(dar_gettext("Continue? "));
	    }
	}
	inherited_warning(message);
    }
