getdim(unsigned char *csec3,g2int *width,g2int *height,g2int *iscan)


{

      g2int  *igdstmpl,*list_opt;
      g2int  *igds;
      g2int  iofst,igdtlen,num_opt,jerr;

      igdstmpl=0;
      list_opt=0;
      igds=0;
      iofst=0;
      jerr= g2_unpack3(csec3,&iofst,&igds,&igdstmpl,
                       &igdtlen,&list_opt,&num_opt);
      if (jerr == 0) {
         switch ( igds[4] )
         {
           case 0:
           case 1:
           case 2:
           case 3:
           {
              *width=igdstmpl[7];
              *height=igdstmpl[8];
              *iscan=igdstmpl[18];
              break;
           }
           case 10:
           {
              *width=igdstmpl[7];
              *height=igdstmpl[8];
              *iscan=igdstmpl[15];
              break;
           }
           case 20:
           {
              *width=igdstmpl[7];
              *height=igdstmpl[8];
              *iscan=igdstmpl[17];
              break;
           }
           case 30:
           {
              *width=igdstmpl[7];
              *height=igdstmpl[8];
              *iscan=igdstmpl[17];
              break;
           }
           case 40:
           case 41:
           case 42:
           case 43:
           {
              *width=igdstmpl[7];
              *height=igdstmpl[8];
              *iscan=igdstmpl[18];
              break;
           }
           case 90:
           {
              *width=igdstmpl[7];
              *height=igdstmpl[8];
              *iscan=igdstmpl[16];
              break;
           }
           case 110:
           {
              *width=igdstmpl[7];
              *height=igdstmpl[8];
              *iscan=igdstmpl[15];
              break;
           }
           default:
           {
              *width=0;
              *height=0;
              *iscan=0;
              break;
           }
         }
      }
      else {
         *width=0;
         *height=0;
      }

      if (igds != 0) free(igds);
      if (igdstmpl != 0) free(igdstmpl);
      if (list_opt != 0) free(list_opt);

      return 0;
}
