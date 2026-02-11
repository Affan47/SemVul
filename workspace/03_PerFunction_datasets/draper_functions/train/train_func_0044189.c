nyx_restore_obarray()
{
   LVAL obvec = getvalue(obarray);
   LVAL sscratch = xlenter("*SCRATCH*");
   int i;


   for (i = 0; i < HSIZE; i++) {
      LVAL last = NULL;
      LVAL dcon;


      for (dcon = getelement(obvec, i); dcon; dcon = cdr(dcon)) {
         LVAL dsym = car(dcon);
         char *name = (char *)getstring(getpname(dsym));
         LVAL scon;


         if (strcmp(name, "*OBARRAY*") == 0) {
            continue;
         }


         if (strcmp(name, "*SCRATCH*") == 0) {
            continue;
         }


         for (scon = getelement(nyx_obarray, hash(name, HSIZE)); scon; scon = cdr(scon)) {
            LVAL ssym = car(scon);


            if (strcmp(name, (char *)getstring(getpname(ssym))) == 0) {
               setvalue(dsym, nyx_dup_value(getvalue(ssym)));
               setplist(dsym, nyx_dup_value(getplist(ssym)));
               setfunction(dsym, nyx_dup_value(getfunction(ssym)));
               break;
            }
         }


         if (scon == NULL) {

            if (findprop(sscratch, dsym) == NIL) {
               if (last) {
                  rplacd(last, cdr(dcon));
               }
               else {
                  setelement(obvec, i, cdr(dcon));
               }
            }
         }


         last = dcon;
      }
   }
}
