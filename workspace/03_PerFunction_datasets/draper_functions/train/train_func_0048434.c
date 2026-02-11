surrender()
{


	if( viewing_nation_recno == from_nation_recno )
	{
		str  = "You have surrendered to ";
		str += to_nation_name();
		str += ".";
	}
	else
	{
		str  = from_nation_name();
		str += " has surrendered to you.";
	}
}
