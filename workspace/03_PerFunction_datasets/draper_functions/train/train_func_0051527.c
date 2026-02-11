hp_probe_parameter_support_table (enum hp_device_compat_e compat,
                                  HpScl scl, int value)

{int k, j;
 char *eptr;
 static int photosmart_output_type[] =

   { HP_COMPAT_PS, SCL_OUTPUT_DATA_TYPE, 0, 4, 5, HP_EOL };

 static int *support_table[] =
 {
   photosmart_output_type
 };

 eptr = getenv ("SANE_HP_CHK_TABLE");
 if ((eptr != NULL) && (*eptr == '0'))
   return SANE_STATUS_EOF;

 for (k = 0; k < (int)(sizeof (support_table)/sizeof (support_table[0])); k++)
 {
   if ((scl == support_table[k][1]) && (support_table[k][0] & compat))
   {
      for (j = 2; support_table[k][j] != HP_EOL; j++)
        if (support_table[k][j] == value) return SANE_STATUS_GOOD;
      return SANE_STATUS_UNSUPPORTED;
   }
 }
 return SANE_STATUS_EOF;
}
