clearkey ( char id )
{
   pbutton pb = firstbutton;
   while ( pb ) {
      if ( pb->id == id ) {
         pb->keynum = 0;
         pb->markedkeynum = 0;
      }
      pb = pb->next;
   }
}
