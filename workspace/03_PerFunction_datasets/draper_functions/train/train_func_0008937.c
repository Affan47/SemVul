process_recover()
{
	if( hit_points==0 || hit_points == max_hit_points )
		return;

	err_when( hit_points > max_hit_points );


   int hitPointsInc;

   if( unit_mode == UNIT_MODE_OVERSEE ||
       unit_mode == UNIT_MODE_IN_HARBOR )
   {
      hitPointsInc = 2;
   }


	else if( unit_mode == UNIT_MODE_ON_SHIP )
	{


      if( unit_array[unit_mode_para]->unit_mode == UNIT_MODE_IN_HARBOR )
         hitPointsInc = 2;
      else
         hitPointsInc = 1;
   }


   else if( cur_action == SPRITE_IDLE )
   {
      hitPointsInc = 1;
   }
   else
      return;


   hit_points += hitPointsInc;

   if( hit_points > max_hit_points )
      hit_points = max_hit_points;
}
