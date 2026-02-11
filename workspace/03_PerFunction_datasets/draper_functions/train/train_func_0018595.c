loyalty()
{
   if( town_recno )
      return (int) town_array[town_recno]->race_loyalty_array[race_id-1];
   else
      return (int) worker_loyalty;
}
