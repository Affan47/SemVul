think_independent_form_new_nation()
{
	if( misc.random(10) > 0 )
		return 0;


	if( population < 30 )
		return 0;


	if( nation_array.all_nation_population > 60 * MAX_NATION )
		return 0;


	if( !nation_array.can_form_new_ai_nation() )
		return 0;


	return form_new_nation();
}
