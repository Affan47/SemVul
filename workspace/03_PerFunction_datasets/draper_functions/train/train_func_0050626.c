buttonpressed(int         id)
{
   tdialogbox::buttonpressed(id);
   switch (id) {

      case 1:
      case 2:   action = id;
        break;
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13: {
            playerbit ^=  1 << ( id-6 ) ;
         anzeige();
      }
   break;
   }
}
