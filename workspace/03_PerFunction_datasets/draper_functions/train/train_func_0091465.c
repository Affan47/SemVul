editGameOptions ( bool mainApp  )
{
   try {
      EditGameOptions ego ( NULL, mainApp );
      ego.Show();
      ego.RunModal();
   }
   catch ( ... ) {
      errorMessage( "An exception was caught" );
   }
}
