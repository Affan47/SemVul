setrule(const char *s) {
   poller->bailIfCalculating() ;
   const char* err = hliferules.setrule(s, this);
   if (err) return err;

   clearcache() ;

   if (hliferules.alternate_rules)
      return "B0-not-Smax rules are not allowed in HashLife.";

   if (hliferules.isHexagonal())
      grid_type = HEX_GRID;
   else if (hliferules.isVonNeumann())
      grid_type = VN_GRID;
   else
      grid_type = SQUARE_GRID;

   return 0 ;
}
