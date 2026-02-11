setup()
{

   vector<ASCString> player;
   for ( int p = 0; p < gamemap->getPlayerCount(); ++p )
      player.push_back( gamemap->getPlayer(p).getName() );

   BitMapEditor bme (recipients, "Select recieving players", player );
   bme.Show();
   bme.RunModal();


   while ( message.find ( "#CRT#" ) != ASCString::npos )
      message.replace ( message.find ( "#CRT#" ), 5, "\n" );
   while ( message.find ( "#crt#" ) != ASCString::npos )
      message.replace ( message.find ( "#crt#" ), 5, "\n" );
   MultiLineEditor( "Message", message );
}
