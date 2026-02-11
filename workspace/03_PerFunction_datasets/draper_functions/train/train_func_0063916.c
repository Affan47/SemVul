SetExpires(const HtDateTime *aDateTime)
{


   if (!aDateTime)
   {
      if (expires)
         delete expires;

      expires=0;

   }
   else
   {


      if (!expires)
         expires = new HtDateTime(*aDateTime);

   }

}
