setEncoded   ( const string& s )
{
   if ( !s.empty () ) {
      if ( s[0] == 'A' )
         password = s;
      else
         password = encodedpassword2string ( atoi ( s.c_str() ));
   } else
      password = s;
}
