p7_hmm_EncodeStatetype(char *typestring)
{
  if      (strcasecmp(typestring, "M") == 0) return p7T_M;
  else if (strcasecmp(typestring, "D") == 0) return p7T_D;
  else if (strcasecmp(typestring, "I") == 0) return p7T_I;
  else if (strcasecmp(typestring, "S") == 0) return p7T_S;
  else if (strcasecmp(typestring, "N") == 0) return p7T_N;
  else if (strcasecmp(typestring, "B") == 0) return p7T_B;
  else if (strcasecmp(typestring, "E") == 0) return p7T_E;
  else if (strcasecmp(typestring, "C") == 0) return p7T_C;
  else if (strcasecmp(typestring, "T") == 0) return p7T_T;
  else if (strcasecmp(typestring, "J") == 0) return p7T_J;
  else if (strcasecmp(typestring, "X") == 0) return p7T_X;
  else return p7T_BOGUS;
}
