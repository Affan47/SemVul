storesinglevar (Long v)
{
 if (v > 0)
 {
   code_byte(STOREGLOBAL);
   code_word(v-1);
 }
 else if (v < 0)
 {
   int number = (-v) - 1;
   if (number < 10) code_byte(STORELOCAL0 + number);
   else
   {
     code_byte(STORELOCAL);
     code_byte(number);
   }
 }
 else
   code_byte(STOREINDEXED0);
}
