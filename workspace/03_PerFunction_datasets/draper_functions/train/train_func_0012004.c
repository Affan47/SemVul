dev_c3725_mb_wic_get_mpsc_chan(struct cisco_card *card,
                                          u_int port_id,
                                          u_int *mpsc_chan)
{
   u_int cid;

   cid = card->subslot_id + port_id;

   switch(cid) {

      case 0x10:
         *mpsc_chan = 1;
         break;


      case 0x11:
         *mpsc_chan = 0;
         break;


      case 0x20:
         *mpsc_chan = 4;
         break;


      case 0x21:
         *mpsc_chan = 2;
         break;


      case 0x30:
         *mpsc_chan = 5;
         break;


      case 0x31:
         *mpsc_chan = 3;
         break;

      default:
         return(-1);
   }

   return(0);
}
