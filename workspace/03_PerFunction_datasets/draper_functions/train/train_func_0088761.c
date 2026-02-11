__pyx_f_9lightning_4impl_14primal_cd_fast_13ModifiedHuber_derivatives(CYTHON_UNUSED struct __pyx_obj_9lightning_4impl_14primal_cd_fast_ModifiedHuber *__pyx_v_self, CYTHON_UNUSED int __pyx_v_j, double __pyx_v_C, int *__pyx_v_indices, double *__pyx_v_data, int __pyx_v_n_nz, double *__pyx_v_y, double *__pyx_v_b, double *__pyx_v_Lp, double *__pyx_v_Lpp, double *__pyx_v_L) {
  int __pyx_v_i;
  int __pyx_v_ii;
  double __pyx_v_val;
  double __pyx_v_tmp;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  long __pyx_t_4;
  __Pyx_RefNannySetupContext("derivatives", 0);


  (__pyx_v_Lp[0]) = 0.0;


  (__pyx_v_Lpp[0]) = 0.0;


  (__pyx_v_L[0]) = 0.0;


  __pyx_t_1 = __pyx_v_n_nz;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_ii = __pyx_t_2;


    __pyx_v_i = (__pyx_v_indices[__pyx_v_ii]);


    __pyx_v_val = ((__pyx_v_data[__pyx_v_ii]) * (__pyx_v_y[__pyx_v_i]));


    __pyx_t_3 = (((__pyx_v_b[__pyx_v_i]) > 2.0) != 0);
    if (__pyx_t_3) {


      __pyx_t_4 = 0;
      (__pyx_v_Lp[__pyx_t_4]) = ((__pyx_v_Lp[__pyx_t_4]) - ((2.0 * __pyx_v_val) * __pyx_v_C));


      __pyx_t_4 = 0;
      (__pyx_v_L[__pyx_t_4]) = ((__pyx_v_L[__pyx_t_4]) + ((4.0 * __pyx_v_C) * ((__pyx_v_b[__pyx_v_i]) - 1.0)));
      goto __pyx_L5;
    }


    __pyx_t_3 = (((__pyx_v_b[__pyx_v_i]) > 0.0) != 0);
    if (__pyx_t_3) {


      __pyx_v_tmp = (__pyx_v_val * __pyx_v_C);


      __pyx_t_4 = 0;
      (__pyx_v_Lp[__pyx_t_4]) = ((__pyx_v_Lp[__pyx_t_4]) - ((__pyx_v_b[__pyx_v_i]) * __pyx_v_tmp));


      __pyx_t_4 = 0;
      (__pyx_v_Lpp[__pyx_t_4]) = ((__pyx_v_Lpp[__pyx_t_4]) + (__pyx_v_val * __pyx_v_tmp));


      __pyx_t_4 = 0;
      (__pyx_v_L[__pyx_t_4]) = ((__pyx_v_L[__pyx_t_4]) + ((__pyx_v_C * (__pyx_v_b[__pyx_v_i])) * (__pyx_v_b[__pyx_v_i])));
      goto __pyx_L5;
    }
    __pyx_L5:;
  }


  __pyx_t_4 = 0;
  (__pyx_v_Lp[__pyx_t_4]) = ((__pyx_v_Lp[__pyx_t_4]) * 2.0);


  __pyx_t_4 = 0;
  (__pyx_v_Lpp[__pyx_t_4]) = ((__pyx_v_Lpp[__pyx_t_4]) * 2.0);


  __Pyx_RefNannyFinishContext();
}
