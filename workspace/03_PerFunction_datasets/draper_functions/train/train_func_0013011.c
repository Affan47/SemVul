__pyx_f_7sklearn_4tree_5_tree_4Tree_find_split(struct __pyx_obj_7sklearn_4tree_5_tree_Tree *__pyx_v_self, __pyx_t_7sklearn_4tree_5_tree_DTYPE_t *__pyx_v_X_ptr, Py_ssize_t __pyx_v_X_stride, int *__pyx_v_X_argsorted_ptr, Py_ssize_t __pyx_v_X_argsorted_stride, __pyx_t_7sklearn_4tree_5_tree_DOUBLE_t *__pyx_v_y_ptr, Py_ssize_t __pyx_v_y_stride, __pyx_t_7sklearn_4tree_5_tree_DOUBLE_t *__pyx_v_sample_weight_ptr, __pyx_t_7sklearn_4tree_5_tree_BOOL_t *__pyx_v_sample_mask_ptr, int __pyx_v_n_node_samples, double __pyx_v_weighted_n_node_samples, int __pyx_v_n_total_samples, int *__pyx_v__best_i, double *__pyx_v__best_t, double *__pyx_v__best_error, double *__pyx_v__initial_error) {
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("find_split", 0);


  __pyx_t_1 = (__pyx_v_self->find_split_algorithm == __pyx_v_7sklearn_4tree_5_tree__TREE_SPLIT_BEST);
  if (__pyx_t_1) {


    ((struct __pyx_vtabstruct_7sklearn_4tree_5_tree_Tree *)__pyx_v_self->__pyx_vtab)->find_best_split(__pyx_v_self, __pyx_v_X_ptr, __pyx_v_X_stride, __pyx_v_X_argsorted_ptr, __pyx_v_X_argsorted_stride, __pyx_v_y_ptr, __pyx_v_y_stride, __pyx_v_sample_weight_ptr, __pyx_v_sample_mask_ptr, __pyx_v_n_node_samples, __pyx_v_weighted_n_node_samples, __pyx_v_n_total_samples, __pyx_v__best_i, __pyx_v__best_t, __pyx_v__best_error, __pyx_v__initial_error);
    goto __pyx_L3;
  }


  __pyx_t_1 = (__pyx_v_self->find_split_algorithm == __pyx_v_7sklearn_4tree_5_tree__TREE_SPLIT_RANDOM);
  if (__pyx_t_1) {


    ((struct __pyx_vtabstruct_7sklearn_4tree_5_tree_Tree *)__pyx_v_self->__pyx_vtab)->find_random_split(__pyx_v_self, __pyx_v_X_ptr, __pyx_v_X_stride, __pyx_v_X_argsorted_ptr, __pyx_v_X_argsorted_stride, __pyx_v_y_ptr, __pyx_v_y_stride, __pyx_v_sample_weight_ptr, __pyx_v_sample_mask_ptr, __pyx_v_n_node_samples, __pyx_v_weighted_n_node_samples, __pyx_v_n_total_samples, __pyx_v__best_i, __pyx_v__best_t, __pyx_v__best_error, __pyx_v__initial_error);
    goto __pyx_L3;
  }
  __pyx_L3:;

  __Pyx_RefNannyFinishContext();
}
