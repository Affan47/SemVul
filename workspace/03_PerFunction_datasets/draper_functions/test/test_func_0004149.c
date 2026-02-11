fits_in (int *shape, int pos)
{
   if (board[pos] || board[pos + shape[1]] ||
       board[pos + shape[2]]  || board[pos + shape[3]])
   {
      return 0;
   }

   return 1;
}
