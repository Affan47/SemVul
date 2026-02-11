true_nation_recno()
{
   if( spy_recno )
      return spy_array[spy_recno]->true_nation_recno;
   else
      return nation_recno;
}
