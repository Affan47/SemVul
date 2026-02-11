__pyx_f_9lightning_4impl_14primal_cd_fast_12SquaredHinge_update(CYTHON_UNUSED struct __pyx_obj_9lightning_4impl_14primal_cd_fast_SquaredHinge *__pyx_v_self, CYTHON_UNUSED int __pyx_v_j, double __pyx_v_z_diff, double __pyx_v_C, int *__pyx_v_indices, double *__pyx_v_data, int __pyx_v_n_nz, double *__pyx_v_y, double *__pyx_v_b, double *__pyx_v_L_new) {
  int __pyx_v_i;
  int __pyx_v_ii;
  double __pyx_v_b_new;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  long __pyx_t_4;
  __Pyx_RefNannySetupContext("update", 0);


  (__pyx_v_L_new[0]) = 0.0;


  __pyx_t_1 = __pyx_v_n_nz;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_ii = __pyx_t_2;


    __pyx_v_i = (__pyx_v_indices[__pyx_v_ii]);


    __pyx_v_b_new = ((__pyx_v_b[__pyx_v_i]) + ((__pyx_v_z_diff * (__pyx_v_data[__pyx_v_ii])) * (__pyx_v_y[__pyx_v_i])));


    (__pyx_v_b[__pyx_v_i]) = __pyx_v_b_new;


    __pyx_t_3 = ((__pyx_v_b_new > 0.0) != 0);
    if (__pyx_t_3) {


      __pyx_t_4 = 0;
      (__pyx_v_L_new[__pyx_t_4]) = ((__pyx_v_L_new[__pyx_t_4]) + (__pyx_v_b_new * __pyx_v_b_new));
      goto __pyx_L5;
    }
    __pyx_L5:;
  }


  __pyx_t_4 = 0;
  (__pyx_v_L_new[__pyx_t_4]) = ((__pyx_v_L_new[__pyx_t_4]) * __pyx_v_C);


  __Pyx_RefNannyFinishContext();
}
