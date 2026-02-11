__pyx_f_7sklearn_5utils_19graph_shortest_path_remove(struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_v_node) {
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __Pyx_RefNannySetupContext("remove");


  __pyx_t_1 = (__pyx_v_node->parent != 0);
  if (__pyx_t_1) {


    __pyx_v_node->parent->rank = (__pyx_v_node->parent->rank - 1);


    __pyx_t_1 = (__pyx_v_node->left_sibling != 0);
    if (__pyx_t_1) {


      __pyx_v_node->parent->children = __pyx_v_node->left_sibling;
      goto __pyx_L4;
    }


    __pyx_t_1 = (__pyx_v_node->right_sibling != 0);
    if (__pyx_t_1) {


      __pyx_v_node->parent->children = __pyx_v_node->right_sibling;
      goto __pyx_L4;
    }
     {


      __pyx_v_node->parent->children = NULL;
    }
    __pyx_L4:;
    goto __pyx_L3;
  }
  __pyx_L3:;


  __pyx_t_1 = (__pyx_v_node->left_sibling != 0);
  if (__pyx_t_1) {


    __pyx_v_node->left_sibling->right_sibling = __pyx_v_node->right_sibling;
    goto __pyx_L5;
  }
  __pyx_L5:;


  __pyx_t_1 = (__pyx_v_node->right_sibling != 0);
  if (__pyx_t_1) {


    __pyx_v_node->right_sibling->left_sibling = __pyx_v_node->left_sibling;
    goto __pyx_L6;
  }
  __pyx_L6:;


  __pyx_v_node->left_sibling = NULL;


  __pyx_v_node->right_sibling = NULL;


  __pyx_v_node->parent = NULL;

  __Pyx_RefNannyFinishContext();
}
