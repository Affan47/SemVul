__pyx_f_7sklearn_5utils_19graph_shortest_path_link(struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciHeap *__pyx_v_heap, struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_v_node) {
  struct __pyx_t_7sklearn_5utils_19graph_shortest_path_FibonacciNode *__pyx_v_linknode;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  int __pyx_t_2;
  int __pyx_t_3;
  __Pyx_RefNannySetupContext("link");


  __pyx_t_1 = ((__pyx_v_heap->roots_by_rank[__pyx_v_node->rank]) == NULL);
  if (__pyx_t_1) {


    (__pyx_v_heap->roots_by_rank[__pyx_v_node->rank]) = __pyx_v_node;
    goto __pyx_L3;
  }
   {


    __pyx_v_linknode = (__pyx_v_heap->roots_by_rank[__pyx_v_node->rank]);


    (__pyx_v_heap->roots_by_rank[__pyx_v_node->rank]) = NULL;


    __pyx_t_1 = (__pyx_v_node->val < __pyx_v_linknode->val);
    if (!__pyx_t_1) {
      __pyx_t_2 = (__pyx_v_node == __pyx_v_heap->min_node);
      __pyx_t_3 = __pyx_t_2;
    } else {
      __pyx_t_3 = __pyx_t_1;
    }
    if (__pyx_t_3) {


      __pyx_f_7sklearn_5utils_19graph_shortest_path_remove(__pyx_v_linknode);


      __pyx_f_7sklearn_5utils_19graph_shortest_path_add_child(__pyx_v_node, __pyx_v_linknode);


      __pyx_f_7sklearn_5utils_19graph_shortest_path_link(__pyx_v_heap, __pyx_v_node);
      goto __pyx_L4;
    }
     {


      __pyx_f_7sklearn_5utils_19graph_shortest_path_remove(__pyx_v_node);


      __pyx_f_7sklearn_5utils_19graph_shortest_path_add_child(__pyx_v_linknode, __pyx_v_node);


      __pyx_f_7sklearn_5utils_19graph_shortest_path_link(__pyx_v_heap, __pyx_v_linknode);
    }
    __pyx_L4:;
  }
  __pyx_L3:;

  __Pyx_RefNannyFinishContext();
}
