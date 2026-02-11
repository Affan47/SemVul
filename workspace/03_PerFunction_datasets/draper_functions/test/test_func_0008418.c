appendbackslash ( char* string )
{
   if ( strlen ( string ) && string[strlen ( string ) -1] != pathdelimitter )
      strcat ( string, pathdelimitterstring );
}
