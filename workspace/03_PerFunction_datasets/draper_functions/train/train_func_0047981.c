__fr_wtnam(int32 ttyp)
{
 int32 wtyp;

 switch ((byte) ttyp) {
  case WIRE: wtyp = N_WIRE; break;
  case TRI: wtyp = N_TRI; break;
  case TRI0: wtyp = N_TRI0; break;
  case TRI1: wtyp = N_TRI1; break;
  case TRIOR: wtyp = N_TRIOR; break;
  case TRIAND: wtyp = N_TRIAND; break;
  case TRIREG: wtyp = N_TRIREG; break;
  case WAND: wtyp = N_WA; break;
  case WOR: wtyp = N_WO; break;

  case SUPPLY0: wtyp = N_SUPPLY0; break;
  case SUPPLY1: wtyp = N_SUPPLY1; break;
  case REG: wtyp = N_REG; break;
  case TIME: wtyp = N_TIME; break;
  case INTEGER: wtyp = N_INT; break;
  case REAL: case REALTIME: wtyp = N_REAL; break;
  case EVENT: wtyp = N_EVENT; break;
  default: wtyp = -1; break;
 }
 return(wtyp);
}
