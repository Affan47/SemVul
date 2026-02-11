set(LogicStates boolean)
{
  if (val == TrueFalse)
    return;

	switch(boolean)
	{case UnKnown:
		break;
   case TrueFalse:
		val = TrueFalse;
		break;
	case True:
		if (val == False)

		  val = TrueFalse;
		else
		  val = True;
		break;
	case False:
		if (val == True)

		  val = TrueFalse;
		else
		val = False;
		break;
	}
}
