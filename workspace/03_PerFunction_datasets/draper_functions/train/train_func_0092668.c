db_case(il, num_cases)
struct il_code *il;
int num_cases;
   {
   register int c;
   int *typ_vect;
   int i, j;
   int num_types;
   int indx;

   il->u[1].n = num_cases;
   indx = 2;
   for (i = 0; i < num_cases; ++i) {


      c = getc(db);
      SkipWhSp(c)
      GetInt(num_types, c)
      il->u[indx++].n = num_types;
      typ_vect = alloc(num_types * sizeof(int));
      il->u[indx++].vect = typ_vect;
      for (j = 0; j < num_types; ++j)
         typ_vect[j] = db_icntyp();

      il->u[indx++].fld = db_inlin();
      }
   }
