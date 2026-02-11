and_cond(cd1, cd2)
struct code *cd1;
struct code *cd2;
   {
   struct code *cd;

   if (cd1 == NULL)
      return cd2;
   else if (cd2 == NULL)
      return cd1;
   else {
      cd = alc_ary(3);
      cd->ElemTyp(0) = A_Ary;
      cd->Array(0) =            cd1;
      cd->ElemTyp(1) = A_Str;
      cd->Str(1) =              " && ";
      cd->ElemTyp(2) = A_Ary;
      cd->Array(2) =            cd2;
      return cd;
      }
   }
