__to_sytyp(char *s, word32 styp)
{
 switch ((byte) styp) {
  case SYM_UNKN: strcpy(s, "--unknown--"); break;
  case SYM_I: strcpy(s, "instance"); break;
  case SYM_M: strcpy(s, "module"); break;
  case SYM_PRIM: strcpy(s, "primitive"); break;
  case SYM_UDP: strcpy(s, "udp define"); break;
  case SYM_N: strcpy(s, "variable"); break;
  case SYM_TSK: strcpy(s, "task"); break;
  case SYM_STSK: strcpy(s, "systask"); break;
  case SYM_LB: strcpy(s, "named block"); break;
  case SYM_F: strcpy(s, "function"); break;
  case SYM_SF: strcpy(s, "sysfunction"); break;
  case SYM_DEF: strcpy(s, "preprocessor `define"); break;
  case SYM_CA: strcpy(s, "continuous assign"); break;
  case SYM_PTH: strcpy(s, "delay path"); break;
  case SYM_TCHK: strcpy(s, "timing check"); break;
  default: __case_terr(__FILE__, __LINE__);
 }
 return(s);
}
