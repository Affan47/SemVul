LBA_to_MSF(long lba,
			      unsigned char *M,
			      unsigned char *S,
			      unsigned char *F){
  if(lba>=-150){
    *M=(lba+150)/(60*75);
    lba-=(*M)*60*75;
    *S=(lba+150)/75;
    lba-=(*S)*75;
    *F=(lba+150);
  }else{
    *M=(lba+450150)/(60*75);
    lba-=(*M)*60*75;
    *S=(lba+450150)/75;
    lba-=(*S)*75;
    *F=(lba+450150);
  }
}
