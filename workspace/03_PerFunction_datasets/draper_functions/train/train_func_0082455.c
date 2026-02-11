__pyx_f_7sklearn_4tree_5_tree_23ClassificationCriterion_init_value(struct __pyx_obj_7sklearn_4tree_5_tree_ClassificationCriterion *__pyx_v_self, double *__pyx_v_buffer_value) {
  int __pyx_v_n_outputs;
  int *__pyx_v_n_classes;
  Py_ssize_t __pyx_v_label_count_stride;
  double *__pyx_v_label_count_init;
  int __pyx_v_k;
  int __pyx_v_c;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int *__pyx_t_2;
  Py_ssize_t __pyx_t_3;
  double *__pyx_t_4;
  int __pyx_t_5;
  __Pyx_RefNannySetupContext("init_value", 0);


  __pyx_t_1 = __pyx_v_self->__pyx_base.n_outputs;
  __pyx_v_n_outputs = __pyx_t_1;


  __pyx_t_2 = __pyx_v_self->n_classes;
  __pyx_v_n_classes = __pyx_t_2;


  __pyx_t_3 = __pyx_v_self->label_count_stride;
  __pyx_v_label_count_stride = __pyx_t_3;


  __pyx_t_4 = __pyx_v_self->label_count_init;
  __pyx_v_label_count_init = __pyx_t_4;


  __pyx_t_1 = __pyx_v_n_outputs;
  for (__pyx_v_k = 0; __pyx_v_k < __pyx_t_1; __pyx_v_k++) {


    __pyx_t_5 = (__pyx_v_n_classes[__pyx_v_k]);
    for (__pyx_v_c = 0; __pyx_v_c < __pyx_t_5; __pyx_v_c++) {


      (__pyx_v_buffer_value[((__pyx_v_k * __pyx_v_label_count_stride) + __pyx_v_c)]) = (__pyx_v_label_count_init[((__pyx_v_k * __pyx_v_label_count_stride) + __pyx_v_c)]);
    }
  }

  __Pyx_RefNannyFinishContext();
}
