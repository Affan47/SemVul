g2_create(unsigned char *cgrib,g2int *listsec0,g2int *listsec1)


{

      g2int  ierr;
      g2int   zero=0,one=1;
      g2int   mapsec1len=MAPSEC1LEN;
      g2int   mapsec1[MAPSEC1LEN]={ 2,2,1,1,1,2,1,1,1,1,1,1,1 };
      g2int   i,lensec0,lensec1,iofst,ibeg,nbits,len;

      ierr=0;


      if (listsec0[1] != 2) {
        printf("g2_create: can only code GRIB edition 2.");
        ierr=-1;
        return (ierr);
      }


      cgrib[0]=0x47;
      cgrib[1]=0x52;
      cgrib[2]=0x49;
      cgrib[3]=0x42;
      sbit(cgrib,&zero,32,16);
      sbit(cgrib,listsec0+0,48,8);
      sbit(cgrib,listsec0+1,56,8);
      lensec0=16;


      ibeg=lensec0*8;
      iofst=ibeg+32;
      sbit(cgrib,&one,iofst,8);
      iofst=iofst+8;


      for (i=0;i<mapsec1len;i++) {
        nbits=mapsec1[i]*8;
        sbit(cgrib,listsec1+i,iofst,nbits);
        iofst=iofst+nbits;
      }


      lensec1=(iofst-ibeg)/8;
      sbit(cgrib,&lensec1,ibeg,32);


      sbit(cgrib,&zero,64,32);
      len=lensec0+lensec1;
      sbit(cgrib,&len,96,32);

      return (len);

}
