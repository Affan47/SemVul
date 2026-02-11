bigpow(da, db, dx)
dptr da, db, dx;
   {
   C_integer r;
   extern int over_flow;


   r = iipow(IntVal(*da), IntVal(*db));
   if (over_flow) {
      k_errornumber = 203;
      k_errortext = "";
      k_errorvalue = nulldesc;
      have_errval = 0;
      return Error;
      }
   MakeInt(r, dx);
   return Succeeded;
   }
