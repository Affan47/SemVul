print_80000001_ebx(unsigned int  value,
                   vendor_t      vendor,
                   unsigned int  val_1_eax)
{
   switch (vendor) {
   case VENDOR_AMD:
      print_80000001_ebx_amd(value, val_1_eax);
      break;
   case VENDOR_INTEL:
   case VENDOR_CYRIX:
   case VENDOR_VIA:
   case VENDOR_TRANSMETA:
   case VENDOR_UMC:
   case VENDOR_NEXGEN:
   case VENDOR_RISE:
   case VENDOR_SIS:
   case VENDOR_NSC:
   case VENDOR_VORTEX:
   case VENDOR_RDC:
   case VENDOR_UNKNOWN:

      break;
   }
}
