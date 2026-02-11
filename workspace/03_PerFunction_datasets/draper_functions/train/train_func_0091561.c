show(void)
{
  if (mapped()==MSFalse)
   {
     map();
     raise();
     grab();
   }
}
