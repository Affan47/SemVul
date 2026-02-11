xsh_mdark_get_ron(xsh_pre* pre,cpl_parameterlist* params,cpl_propertylist* qc_log,xsh_instrument* instr)
{

   int fpn_llx=0;
   int fpn_lly=0;
   int fpn_urx=0;
   int fpn_ury=0;
   cpl_size fpn_hsize=0;
   cpl_size fpn_nsamp=0;
   int sx=0;
   int sy=0;
   cpl_size zone[4];
   double qc_ron_val=0;
   double qc_ron_err=0;
   double median=0;


   XSH_ASSURE_NOT_NULL_MSG(pre, "Null input pre");
   XSH_ASSURE_NOT_NULL_MSG(params, "Null input parameters");
   XSH_ASSURE_NOT_NULL_MSG(qc_log, "Null input QC propertylist");

   sx=xsh_pre_get_nx(pre);
   sy=xsh_pre_get_ny(pre);


   check(fpn_llx=xsh_parameters_get_int(params,"xsh_mdark","fpn_llx"));
   check(fpn_lly=xsh_parameters_get_int(params,"xsh_mdark","fpn_lly"));
   check(fpn_urx=xsh_parameters_get_int(params,"xsh_mdark","fpn_urx"));
   check(fpn_ury=xsh_parameters_get_int(params,"xsh_mdark","fpn_ury"));
   check(fpn_hsize=xsh_parameters_get_int(params,"xsh_mdark","fpn_hsize"));
   check(fpn_nsamp=xsh_parameters_get_int(params,"xsh_mdark","fpn_nsamples"));


   if(fpn_llx == -1) fpn_llx=1;
   if(fpn_lly == -1) fpn_lly=1;
   if(fpn_urx == -1) fpn_urx=sx;
   if(fpn_ury == -1) fpn_ury=sy;

   fpn_llx = (fpn_llx>0) ? fpn_llx : 1;
   fpn_lly = (fpn_lly>0) ? fpn_lly : 1;
   fpn_urx = (fpn_urx<sx) ? fpn_urx : sx;
   fpn_ury = (fpn_ury<sy) ? fpn_ury : sy;

   assure(fpn_urx>fpn_llx,CPL_ERROR_ILLEGAL_INPUT,
          "Must be fpn_urx (%d) >  fpn_llx (%d)",
          fpn_urx,fpn_llx);

   assure(fpn_ury>fpn_lly,CPL_ERROR_ILLEGAL_INPUT,
          "Must be fpn_ury (%d) >  fpn_lly (%d)",
          fpn_ury,fpn_lly);


   zone[0]=fpn_llx;
   zone[1]=fpn_urx;
   zone[2]=fpn_lly;
   zone[3]=fpn_ury;

   check(xsh_image_flag_bp(pre->data,pre->qual,instr));
   check_msg(cpl_flux_get_noise_window(pre->data, zone, fpn_hsize,fpn_nsamp,
                                       &qc_ron_val, &qc_ron_err),
             "Error computing noise in a window");


   double inv_sqrt2=1./sqrt(2);
   xsh_pfits_set_qc_ron(qc_log,qc_ron_val*inv_sqrt2);
   xsh_pfits_set_qc_ron_err(qc_log,qc_ron_err*inv_sqrt2) ;


  cleanup:

   return cpl_error_get_code();

}
