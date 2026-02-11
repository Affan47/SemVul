__pyx_f_9lightning_4impl_8sag_fast_9L1Penalty_projection(CYTHON_UNUSED struct __pyx_obj_9lightning_4impl_8sag_fast_L1Penalty *__pyx_v_self, double *__pyx_v_w, int *__pyx_v_indices, double __pyx_v_stepsize, double __pyx_v_w_scale, int __pyx_v_n_nz) {
  int __pyx_v_j;
  int __pyx_v_jj;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  __Pyx_RefNannySetupContext("projection", 0);


  __pyx_t_1 = __pyx_v_n_nz;
  for (__pyx_t_2 = 0; __pyx_t_2 < __pyx_t_1; __pyx_t_2+=1) {
    __pyx_v_jj = __pyx_t_2;


    __pyx_v_j = (__pyx_v_indices[__pyx_v_jj]);


    (__pyx_v_w[__pyx_v_j]) = (fmax(((__pyx_v_w[__pyx_v_j]) - (__pyx_v_stepsize * __pyx_v_w_scale)), 0.0) - fmax(((-(__pyx_v_w[__pyx_v_j])) - (__pyx_v_stepsize * __pyx_v_w_scale)), 0.0));
  }


  __Pyx_RefNannyFinishContext();
}
