Choose_LocalParmTable (unsigned short int center,
                                               unsigned short int subcenter,
                                               size_t *tableLen)
{
   switch (center) {
      case 7:


         switch (subcenter) {
            case 5:
               *tableLen = sizeof (HPC_LclTable) / sizeof (GRIB2LocalTable);
               return &HPC_LclTable[0];
            default:
               *tableLen = sizeof (NCEP_LclTable) / sizeof (GRIB2LocalTable);
               return &NCEP_LclTable[0];


         }
      case 8:
         switch (subcenter) {
            case GRIB2MISSING_u2:
            case 0:
               *tableLen = sizeof (NDFD_LclTable) / sizeof (GRIB2LocalTable);
               return &NDFD_LclTable[0];
            default:
               *tableLen = 0;
               return NULL;
         }
      default:
         *tableLen = 0;
         return NULL;
   }
}
