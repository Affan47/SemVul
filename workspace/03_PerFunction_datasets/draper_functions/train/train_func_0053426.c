getDescription() const
{
   ASCString res = "Remove mine at " + pos.toString(false) + " with id " + ASCString::toString(mineID);
   return  res;
}
