__pyx_f_7sklearn_5utils_19graph_shortest_path_add_sibling(struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_v_node, struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_v_new_sibling) {
  struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_v_temp;
  __Pyx_RefNannyDeclarations
  struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_t_1;
  int __pyx_t_2;
  __Pyx_RefNannySetupContext("add_sibling", 0);


  __pyx_v_temp = __pyx_f_7sklearn_5utils_19graph_shortest_path_rightmost_sibling(__pyx_v_node);


  __pyx_v_temp->right_sibling = __pyx_v_new_sibling;


  __pyx_v_new_sibling->left_sibling = __pyx_v_temp;


  __pyx_v_new_sibling->right_sibling = NULL;


  __pyx_t_1 = __pyx_v_node->parent;
  __pyx_v_new_sibling->parent = __pyx_t_1;


  __pyx_t_2 = (__pyx_v_new_sibling->parent != 0);
  if (__pyx_t_2) {


    __pyx_v_new_sibling->parent->rank = (__pyx_v_new_sibling->parent->rank + 1);
    goto __pyx_L3;
  }
  __pyx_L3:;

  __Pyx_RefNannyFinishContext();
}
