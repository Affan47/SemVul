__pyx_f_7sklearn_9neighbors_9ball_tree_8BallTree_query_radius_count_(struct __pyx_obj_7sklearn_9neighbors_9ball_tree_BallTree *__pyx_v_self, __pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t *__pyx_v_pt, __pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t __pyx_v_r, struct __pyx_t_7sklearn_9neighbors_9ball_tree_stack *__pyx_v_node_stack) {
  __pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t *__pyx_v_data;
  __pyx_t_7sklearn_9neighbors_9ball_tree_ITYPE_t *__pyx_v_idx_array;
  __pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t *__pyx_v_node_centroid_arr;
  struct __pyx_t_7sklearn_9neighbors_9ball_tree_NodeInfo *__pyx_v_node_info_arr;
  struct __pyx_t_7sklearn_9neighbors_9ball_tree_NodeInfo *__pyx_v_node_info;
  __pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t __pyx_v_p;
  __pyx_t_7sklearn_9neighbors_9ball_tree_ITYPE_t __pyx_v_n_features;
  __pyx_t_7sklearn_9neighbors_9ball_tree_ITYPE_t __pyx_v_i;
  __pyx_t_7sklearn_9neighbors_9ball_tree_ITYPE_t __pyx_v_i_node;
  __pyx_t_7sklearn_9neighbors_9ball_tree_ITYPE_t __pyx_v_count;
  __pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t __pyx_v_r_p;
  __pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t __pyx_v_dist_pt;
  struct __pyx_t_7sklearn_9neighbors_9ball_tree_stack_item __pyx_v_item;
  __pyx_t_7sklearn_9neighbors_9ball_tree_ITYPE_t __pyx_r;
  __Pyx_RefNannyDeclarations
  int __pyx_t_1;
  __pyx_t_7sklearn_9neighbors_9ball_tree_ITYPE_t __pyx_t_2;
  long __pyx_t_3;
  __Pyx_RefNannySetupContext("query_radius_count_");


  __pyx_v_data = ((__pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t *)__pyx_v_self->data->data);


  __pyx_v_idx_array = ((__pyx_t_7sklearn_9neighbors_9ball_tree_ITYPE_t *)__pyx_v_self->idx_array->data);


  __pyx_v_node_centroid_arr = ((__pyx_t_7sklearn_9neighbors_9ball_tree_DTYPE_t *)__pyx_v_self->node_centroid_arr->data);


  __pyx_v_node_info_arr = ((struct __pyx_t_7sklearn_9neighbors_9ball_tree_NodeInfo *)__pyx_v_self->node_info_arr->data);


  __pyx_v_node_info = __pyx_v_node_info_arr;


  __pyx_v_p = __pyx_v_self->p;


  __pyx_v_n_features = (__pyx_v_self->data->dimensions[1]);


  __pyx_v_count = 0;


  __pyx_v_r_p = __pyx_f_7sklearn_9neighbors_9ball_tree_dist_p_from_dist(__pyx_v_r, __pyx_v_p);


  __pyx_v_item.i_node = 0;


  __pyx_f_7sklearn_9neighbors_9ball_tree_stack_push(__pyx_v_node_stack, __pyx_v_item);


  while (1) {
    __pyx_t_1 = (__pyx_v_node_stack->n > 0);
    if (!__pyx_t_1) break;


    __pyx_v_item = __pyx_f_7sklearn_9neighbors_9ball_tree_stack_pop(__pyx_v_node_stack);


    __pyx_v_i_node = __pyx_v_item.i_node;


    __pyx_v_node_info = (__pyx_v_node_info_arr + __pyx_v_i_node);


    __pyx_v_dist_pt = __pyx_f_7sklearn_9neighbors_9ball_tree_dist(__pyx_v_pt, (__pyx_v_node_centroid_arr + (__pyx_v_n_features * __pyx_v_i_node)), __pyx_v_n_features, __pyx_v_p);


    __pyx_t_1 = ((__pyx_v_dist_pt - __pyx_v_node_info->radius) > __pyx_v_r);
    if (__pyx_t_1) {


      goto __pyx_L3_continue;
      goto __pyx_L5;
    }


    __pyx_t_1 = ((__pyx_v_dist_pt + __pyx_v_node_info->radius) < __pyx_v_r);
    if (__pyx_t_1) {


      __pyx_v_count = (__pyx_v_count + (__pyx_v_node_info->idx_end - __pyx_v_node_info->idx_start));
      goto __pyx_L5;
    }


    if (__pyx_v_node_info->is_leaf) {


      __pyx_t_2 = __pyx_v_node_info->idx_end;
      for (__pyx_v_i = __pyx_v_node_info->idx_start; __pyx_v_i < __pyx_t_2; __pyx_v_i++) {


        __pyx_v_dist_pt = __pyx_f_7sklearn_9neighbors_9ball_tree_dist_p(__pyx_v_pt, (__pyx_v_data + ((__pyx_v_idx_array[__pyx_v_i]) * __pyx_v_n_features)), __pyx_v_n_features, __pyx_v_p);


        __pyx_t_1 = (__pyx_v_dist_pt <= __pyx_v_r_p);
        if (__pyx_t_1) {


          __pyx_v_count = (__pyx_v_count + 1);
          goto __pyx_L8;
        }
        __pyx_L8:;
      }
      goto __pyx_L5;
    }
     {


      __pyx_v_item.i_node = ((2 * __pyx_v_i_node) + 1);


      __pyx_f_7sklearn_9neighbors_9ball_tree_stack_push(__pyx_v_node_stack, __pyx_v_item);


      __pyx_t_3 = ((2 * __pyx_v_i_node) + 2);
      __pyx_v_item.i_node = __pyx_t_3;
      __pyx_v_i = __pyx_t_3;


      __pyx_f_7sklearn_9neighbors_9ball_tree_stack_push(__pyx_v_node_stack, __pyx_v_item);
    }
    __pyx_L5:;
    __pyx_L3_continue:;
  }


  __pyx_r = __pyx_v_count;
  goto __pyx_L0;

  __pyx_r = 0;
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}
