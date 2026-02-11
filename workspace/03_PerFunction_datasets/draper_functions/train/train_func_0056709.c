run ( void )
{
   mousevisible(true);
   do {
     tdialogbox::run();
   } while ( status < 10 );
}
