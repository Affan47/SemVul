firm_worn_out(int firmRecno)
{
	Firm* firmPtr = firm_array[firmRecno];

	err_when( firmPtr->nation_recno != nation_array.player_recno );

	News* newsPtr = add_news( NEWS_FIRM_WORN_OUT, NEWS_NORMAL, firmPtr->nation_recno);

	if( !newsPtr )
		return;

	newsPtr->short_para1 = firmPtr->firm_id;

	if( firmPtr->closest_town_name_id )
		newsPtr->short_para2 = firmPtr->closest_town_name_id;
	else
		newsPtr->short_para2 = firmPtr->get_closest_town_name_id();
}
