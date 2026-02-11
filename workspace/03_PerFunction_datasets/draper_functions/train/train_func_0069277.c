ooIsVideoDataTypeSupported
   (OOH323CallData *call, H245VideoCapability* pVideoCap, int dir)
{
   switch(pVideoCap->t)
   {
   case T_H245VideoCapability_h263VideoCapability:
      if(pVideoCap->u.h263VideoCapability->m.sqcifMPIPresent)
         return ooIsVideoDataTypeH263Supported(call,
                    pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_SQCIF);
      else if(pVideoCap->u.h263VideoCapability->m.qcifMPIPresent)
         return ooIsVideoDataTypeH263Supported(call,
                     pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_QCIF);
      else if(pVideoCap->u.h263VideoCapability->m.cifMPIPresent)
        return ooIsVideoDataTypeH263Supported(call,
                      pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_CIF);
      else if(pVideoCap->u.h263VideoCapability->m.cif4MPIPresent)
        return ooIsVideoDataTypeH263Supported(call,
                     pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_CIF4);
      else if(pVideoCap->u.h263VideoCapability->m.cif16MPIPresent)
        return ooIsVideoDataTypeH263Supported(call,
                    pVideoCap->u.h263VideoCapability, dir, OO_PICFORMAT_CIF16);
      break;
   case T_H245VideoCapability_nonStandard:
   case T_H245VideoCapability_h261VideoCapability:
   case T_H245VideoCapability_h262VideoCapability:
   case T_H245VideoCapability_is11172VideoCapability:
   case T_H245VideoCapability_genericVideoCapability:
   case T_H245VideoCapability_extElem1:
   default:
     OOTRACEDBGA1("Unsupported video capability type in "
                  "ooIsVideoDataTypeSupported\n");
      return NULL;
   }
   return NULL;
}
