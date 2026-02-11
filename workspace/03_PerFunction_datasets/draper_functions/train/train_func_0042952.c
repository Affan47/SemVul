Next(Real mu)
{
   if (mu <= 0)
   {
      if (mu == 0) return 0;
      else Throw(Logic_error("Newran: illegal parameters"));
   }
   if (mu < 10) return Next_very_small(mu);
   else if (mu < 100) return Next_small(mu);
   else if (mu < 200)
   {

      int i = (int)P100.Next();
      return i + Next_small(mu - 100);
   }
   else if (mu < 300)
   {

      int i = (int)P200.Next();
      return i + Next_small(mu - 200);
   }
   else return Next_large(mu);
}
