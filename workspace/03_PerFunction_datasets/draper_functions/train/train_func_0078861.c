__pyx_fill_contig_strides_array(Py_ssize_t *__pyx_v_shape, Py_ssize_t *__pyx_v_strides, Py_ssize_t __pyx_v_stride, int __pyx_v_ndim, char __pyx_v_order) {
  int __pyx_v_idx;
  Py_ssize_t __pyx_r;
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;


  __pyx_t_1 = (__pyx_v_order == 'F');
  if (__pyx_t_1) {


    __pyx_t_2 = __pyx_v_ndim;
    for (__pyx_t_3 = 0; __pyx_t_3 < __pyx_t_2; __pyx_t_3+=1) {
      __pyx_v_idx = __pyx_t_3;


      (__pyx_v_strides[__pyx_v_idx]) = __pyx_v_stride;


      __pyx_v_stride = (__pyx_v_stride * (__pyx_v_shape[__pyx_v_idx]));
    }
    goto __pyx_L3;
  }
   {


    for (__pyx_t_2 = (__pyx_v_ndim - 1); __pyx_t_2 > -1; __pyx_t_2-=1) {
      __pyx_v_idx = __pyx_t_2;


      (__pyx_v_strides[__pyx_v_idx]) = __pyx_v_stride;


      __pyx_v_stride = (__pyx_v_stride * (__pyx_v_shape[__pyx_v_idx]));
    }
  }
  __pyx_L3:;


  __pyx_r = __pyx_v_stride;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  return __pyx_r;
}
