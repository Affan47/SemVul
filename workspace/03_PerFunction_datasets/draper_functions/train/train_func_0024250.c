detect_nation()
{


	if( browse_nation.detect() )
	{
		browse_nation_recno = browse_nation.recno();
		return;
	}


	if( detect_button() )
		return;


	detect_detail();
}
