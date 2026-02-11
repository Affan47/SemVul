appendbackslash ( ASCString& string )
{
   if ( !string.empty()  && string[ string.length() -1] != pathdelimitter )
      string += pathdelimitterstring ;
}
