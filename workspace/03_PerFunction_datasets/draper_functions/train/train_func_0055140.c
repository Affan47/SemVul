sell_firm(char remoteAction)
{
   if( !remoteAction && remote.is_enable() )
   {

      short *shortPtr = (short *)remote.new_send_queue_msg(MSG_FIRM_SELL, sizeof(short));
      *shortPtr = firm_recno;
      return;
   }


	Nation* nationPtr = nation_array[nation_recno];

	int sellIncome = firm_res[firm_id]->setup_cost / 2 * (int) hit_points / (int) max_hit_points;

	nationPtr->add_income(INCOME_SELL_FIRM, (float)sellIncome);

	se_res.sound(center_x, center_y, 1, 'F', firm_id, "SELL" );

   firm_array.del_firm(firm_recno);
}
