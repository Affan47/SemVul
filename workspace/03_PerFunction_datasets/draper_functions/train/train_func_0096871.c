UniqueStatetype(int type)
{
  switch (type) {
  case DUMMY:   return "DUMMY";
  case ROOT_S:  return "ROOT_S";
  case ROOT_IL: return "ROOT_IL";
  case ROOT_IR: return "ROOT_IR";
  case BEGL_S : return "BEGL_S";
  case BEGR_S : return "BEGR_S";
  case BEGR_IL: return "BEGR_IL";
  case MATP_MP: return "MATP_MP";
  case MATP_ML: return "MATP_ML";
  case MATP_MR: return "MATP_MR";
  case MATP_D : return "MATP_D";
  case MATP_IL: return "MATP_IL";
  case MATP_IR: return "MATP_IR";
  case MATL_ML: return "MATL_ML";
  case MATL_D : return "MATL_D";
  case MATL_IL: return "MATL_IL";
  case MATR_MR: return "MATR_MR";
  case MATR_D : return "MATR_D";
  case MATR_IR: return "MATR_IR";
  case END_E  : return "END_E";
  case BIF_B  : return "BIF_B";
  case END_EL : return "END_EL";
  default: cm_Fail("bogus unique state type %d\n", type);
  }
  return "";
}
