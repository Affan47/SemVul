find_d_z_abl(chain_list* abl, long value)
{

  if (ABL_ATOM(abl)) {
      if (ABL_ATOM_VALUE(abl)==getablatomdc()) {


         ABL_CAR_L(abl)=value?getablatomone():getablatomzero();
      }
      else if (ABL_ATOM_VALUE(abl)==getablatomtristate()){


         ABL_CAR_L(abl)=getablatomone();
      }
      return;
   }


   switch (ABL_OPER(abl)) {
      case ABL_OR: case ABL_NOR: value=1;
      case ABL_AND: case ABL_NAND: value=0;
   }


   for (abl=ABL_CDR(abl); abl; abl=ABL_CDR(abl)) {
      find_d_z_abl(ABL_CAR(abl),value);
   }

}
