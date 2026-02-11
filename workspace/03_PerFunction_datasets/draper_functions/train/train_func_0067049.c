xsh_bpmap_2pre(cpl_frame* bpmap,const char* prefix, xsh_instrument* inst)
{
   cpl_frame* result=NULL;
   xsh_pre* pre=NULL;
   char* tag=NULL;
   char* name=NULL;

   pre= xsh_pre_create(bpmap,NULL,NULL,inst,0,false);
   tag=cpl_sprintf("%s_%s",prefix,xsh_instrument_arm_tostring(inst));
   name=cpl_sprintf("%s.fits",tag);

   if(strstr(tag,XSH_BP_MAP_NL)!=NULL) {
        xsh_bpmap_bitwise_to_flag(pre->data,QFLAG_NON_LINEAR_PIXEL);
   }
   result=xsh_pre_save(pre,name,tag,1 );

   xsh_pre_free(&pre);
   XSH_FREE(tag);
   XSH_FREE(name);
   return result;
}
