is_attr_prior2(lListElem *upper_el, double lower_value, int t_value, int t_dominant ){
   u_long32 relop;
   u_long32 dom;
   bool ret;
   double upper_value;

   DENTER(BASIS_LAYER, "is_attr_prior2");

   if ((dom = lGetUlong(upper_el, t_dominant)) == 0 || (dom & DOMINANT_TYPE_VALUE) ){
      DRETURN(false);
   }

   relop = lGetUlong(upper_el, CE_relop);
   if ((relop == CMPLXEQ_OP || relop == CMPLXNE_OP)) {
      DRETURN(true);
   }

   upper_value = lGetDouble(upper_el, t_value);

   if (relop == CMPLXGE_OP || relop == CMPLXGT_OP ){
      ret = upper_value >= lower_value ? true : false;
   } else {
      ret = upper_value <= lower_value ? true : false;
   }
   DRETURN(ret);
}
