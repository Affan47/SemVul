stop_attack_nation(short nationRecno)
{
   FirmMonster* firmMonster;

   for(int i=firm_array.size(); i>0; i--)
   {
      if( firm_array.is_deleted(i) || firm_array[i]->firm_id != FIRM_MONSTER )
         continue;

      firmMonster = (FirmMonster*) firm_array[i];

      firmMonster->reset_hostile_nation(nationRecno);
   }
}
