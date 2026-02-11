key(KeySym keysym_,unsigned int,const char *)
{
  if (keysym_==XK_Return)
   {
     arm();
     activate();
     disarm();
   }
}
