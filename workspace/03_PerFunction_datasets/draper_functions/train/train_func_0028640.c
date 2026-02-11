CalculateStateIndex(CM_t *cm, int node, char utype)
{
  int base;

  base = cm->nodemap[node];
  switch (utype) {
  case ROOT_S:  return base;
  case ROOT_IL: return base+1;
  case ROOT_IR: return base+2;
  case BEGL_S:  return base;
  case BEGR_S:  return base;
  case BEGR_IL: return base+1;
  case MATP_MP: return base;
  case MATP_ML: return base+1;
  case MATP_MR: return base+2;
  case MATP_D:  return base+3;
  case MATP_IL: return base+4;
  case MATP_IR: return base+5;
  case MATL_ML: return base;
  case MATL_D:  return base+1;
  case MATL_IL: return base+2;
  case MATR_MR: return base;
  case MATR_D:  return base+1;
  case MATR_IR: return base+2;
  case END_E:   return base;
  case BIF_B:   return base;
  default: cm_Fail("bogus utype %d in CalculateStateIndex()", utype);
  }
  return base;
}
