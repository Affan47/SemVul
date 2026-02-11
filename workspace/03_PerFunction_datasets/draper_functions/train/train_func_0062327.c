__pyx_f_7sklearn_5utils_19graph_shortest_path_leftmost_sibling(struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_v_node) {
  struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_v_temp;
  struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("leftmost_sibling");


  __pyx_v_temp = __pyx_v_node;


  while (1) {
    __pyx_t_1 = (__pyx_v_temp->left_sibling != 0);
    if (!__pyx_t_1) break;


    __pyx_v_temp = __pyx_v_temp->left_sibling;
  }


  __pyx_r = __pyx_v_temp;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
