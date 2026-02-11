putscoreOnly(int nr, short y) {
#ifndef foo
  static long adr;
  static short xx,yy;
  static uchar len,mask,col;
  static uchar *dp;
  static uchar *adr3;

  adr=184;
  mask=adr >> 16;
  adr=adr & 65535;
  dp=score;

  vga_setpage(mask);

  if (adr < SCR_AB) {


    for (yy=0; yy<=15; yy++) {
      for (xx=0; xx<=255; xx++) {
	adr3=vga_ptr+adr++;
	*(adr3)=*(dp++);
      }
      adr+=384;
    }

  }
  else {

    for (yy=0; yy<=15; yy++) {


      if (adr>SCR_AP) {


	if (adr<=65535) {

          len=(65536-adr);

          for(xx=len; xx>=1; xx--) {
	    adr3=vga_ptr+adr++;
	    *(adr3)=*(dp++);

          }

          mask++;
	  vga_setpage(mask);
          adr=0;

          for(xx=(256-len); xx>=1; xx--) {
	    adr3=vga_ptr+adr++;
	    *(adr3)=*(dp++);
	  }
        }
        else {
          mask++;
	  vga_setpage(mask);
          adr=adr & 65535;
          for (xx=0; xx<=255; xx++) {
	    adr3=vga_ptr+adr++;
	    *(adr3)=*(dp++);

          }
        }
      }
      else {
        for (xx=0; xx<=255; xx++) {
	  adr3=vga_ptr+adr++;
	  *(adr3)=*(dp++);
        }
      }
      adr+=384;
    }
  }
#endif
}
