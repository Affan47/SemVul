cyber_cleanup_overlay(void)
{

     cyber_seqreg_mask(0xA7, 0x0, ~0x5);


     if (!overlay_init)
          return;
     overlay_init = 0;


     cyber_grphw(0x74, savedReg74);
     cyber_grphw(0x75, savedReg75);

     cyber_grphw(0xD9, savedRegD9[0]);
     cyber_grphw(0xDA, savedRegDA[0]);
     cyber_grphw(0xDD, savedRegDD[0]);

     cyber_seqw(0xD9, savedRegD9[1]);
     cyber_seqw(0xDA, savedRegDA[1]);
     cyber_seqw(0xDD, savedRegDD[1]);
}
