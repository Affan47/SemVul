__pyx_f_7sklearn_12linear_model_8sgd_fast_l1penalty(struct __pyx_obj_7sklearn_5utils_13weight_vector_WeightVector *__pyx_v_w, __pyx_t_7sklearn_12linear_model_8sgd_fast_DOUBLE *__pyx_v_q_data_ptr, __pyx_t_7sklearn_12linear_model_8sgd_fast_INTEGER *__pyx_v_x_ind_ptr, int __pyx_v_xnnz, double __pyx_v_u) {
  double __pyx_v_z;
  int __pyx_v_j;
  int __pyx_v_idx;
  double __pyx_v_wscale;
  double *__pyx_v_w_data_ptr;
  __Pyx_RefNannyDeclarations
  double __pyx_t_1;
  __pyx_t_7sklearn_5utils_13weight_vector_DOUBLE *__pyx_t_2;
  int __pyx_t_3;
  int __pyx_t_4;
  int __pyx_t_5;
  int __pyx_t_6;
  __Pyx_RefNannySetupContext("l1penalty", 0);


  __pyx_v_z = 0.0;


  __pyx_v_j = 0;


  __pyx_v_idx = 0;


  __pyx_t_1 = __pyx_v_w->wscale;
  __pyx_v_wscale = __pyx_t_1;


  __pyx_t_2 = __pyx_v_w->w_data_ptr;
  __pyx_v_w_data_ptr = __pyx_t_2;


  __pyx_t_3 = __pyx_v_xnnz;
  for (__pyx_t_4 = 0; __pyx_t_4 < __pyx_t_3; __pyx_t_4+=1) {
    __pyx_v_j = __pyx_t_4;


    __pyx_v_idx = (__pyx_v_x_ind_ptr[__pyx_v_j]);


    __pyx_v_z = (__pyx_v_w_data_ptr[__pyx_v_idx]);


    __pyx_t_5 = ((__pyx_v_wscale * (__pyx_v_w_data_ptr[__pyx_v_idx])) > 0.0);
    if (__pyx_t_5) {


      (__pyx_v_w_data_ptr[__pyx_v_idx]) = __pyx_f_7sklearn_12linear_model_8sgd_fast_max(0.0, ((__pyx_v_w_data_ptr[__pyx_v_idx]) - ((__pyx_v_u + (__pyx_v_q_data_ptr[__pyx_v_idx])) / __pyx_v_wscale)));
      goto __pyx_L5;
    }


    __pyx_t_5 = ((__pyx_v_wscale * (__pyx_v_w_data_ptr[__pyx_v_idx])) < 0.0);
    if (__pyx_t_5) {


      (__pyx_v_w_data_ptr[__pyx_v_idx]) = __pyx_f_7sklearn_12linear_model_8sgd_fast_min(0.0, ((__pyx_v_w_data_ptr[__pyx_v_idx]) + ((__pyx_v_u - (__pyx_v_q_data_ptr[__pyx_v_idx])) / __pyx_v_wscale)));
      goto __pyx_L5;
    }
    __pyx_L5:;


    __pyx_t_6 = __pyx_v_idx;
    (__pyx_v_q_data_ptr[__pyx_t_6]) = ((__pyx_v_q_data_ptr[__pyx_t_6]) + (__pyx_v_wscale * ((__pyx_v_w_data_ptr[__pyx_v_idx]) - __pyx_v_z)));
  }

  __Pyx_RefNannyFinishContext();
}
