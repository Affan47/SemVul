operator+=( const FuncProfS & a )
{
   if( funcid == 0 )
      funcid = a.funcid;

   count += a.count;
   incl += a.incl;
   excl += a.excl;

   return *this;
}
