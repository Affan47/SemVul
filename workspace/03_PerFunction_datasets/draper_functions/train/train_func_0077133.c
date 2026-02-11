deinit()
{
	if( !firm_recno )
      return;

	deinit_derived();

	remove_firm = 1;


	if(firm_ai)
	{
		Nation* nationPtr = nation_array[nation_recno];

		if( should_close_flag )
			nationPtr->firm_should_close_array[firm_id-1]--;

		err_when( nationPtr->firm_should_close_array[firm_id-1] < 0 );

		nationPtr->del_firm_info(firm_id, firm_recno);
	}


	restore_world_matrix();
	release_link();


	if( !sys.signal_exit_flag )
	{

		if( !under_construction )
		{


			FirmDie firmDie;
			firmDie.init(this);
			firm_die_array.add(&firmDie);
		}


		assign_overseer(0);

		if( worker_array )
		{
			resign_all_worker();
			mem_del( worker_array );
			worker_array = NULL;
		}

		if(builder_recno)
			mobilize_builder(builder_recno);
	}
	else
	{
		if(builder_recno)
			kill_builder(builder_recno);

		kill_overseer();

		if(worker_array)
		{
			kill_all_worker();
			mem_del(worker_array);
			worker_array = NULL;
		}
	}


   if( nation_recno )
      nation_array[nation_recno]->nation_firm_count--;


	FirmInfo* firmInfo = firm_res[firm_id];

	firmInfo->total_firm_count--;

	if( nation_recno )
		firmInfo->dec_nation_firm_count(nation_recno);


   loc_x1 = -1;


   if( firm_array.selected_recno == firm_recno )
   {
		firm_array.selected_recno = 0;
      info.disp();
   }


   firm_recno = 0;
	remove_firm = 0;
}
