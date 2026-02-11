short_transition(Regexp *regexp, const char c)
{
	switch(regexp->state)
	{
		case INITIAL:
			if(isdigit(c))
				regexp->state = DIGIT;
			break;
		case DIGIT:
			if(!isdigit(c))
				regexp->state = FINAL;
			break;
		default:
			break;
	}
}
