fontfcnA(env,mode,Font_Ptr)
char *env;
int  *mode;
psfont *Font_Ptr;

{
  int i, result;


  FontP=Font_Ptr;

  InitImager();


  for (i=1; i<MAXTRIAL; i++){
    vm_init_count=0;


    vm_init_amount=MAX_STRING_LEN * 4 * i;
    if (!(initFont())) {

      *mode = SCAN_OUT_OF_MEMORY;
      return(FALSE);
    }

    if ((result=readFont(env))==0){

      vm_used=vm_next_byte();
      return(TRUE);
    }
    else{


      free(vm_base);
    }
  }

  *mode = result;
  return(FALSE);

}
