setup ()
{
   viewingPlayer = editInt("Viewing Player",viewingPlayer,0,7);
   providingPlayer = editInt("Providing Player",providingPlayer,0,7);

   vector<ASCString> list;
   list.push_back ( "Disable View Sharing");
   list.push_back ( "Enable View Sharing");

   enable = chooseString ( "Action", list, enable );
}
