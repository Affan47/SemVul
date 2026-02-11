get_class_weight_ordering( clsf_DS clsf)
{
  int i_class, *class_weight_ordering;
  sort_cell_DS sort_list, temp_sort_list;
  int (* comp_func) () = float_sort_cell_compare_gtr;

  sort_list = (sort_cell_DS) malloc( clsf->n_classes * sizeof( struct sort_cell));
  class_weight_ordering = (int *) malloc( clsf->n_classes * sizeof( int));
  temp_sort_list = sort_list;
  for (i_class=0; i_class<clsf->n_classes; i_class++) {
    temp_sort_list->float_value = clsf->classes[i_class]->w_j;
    temp_sort_list->int_value = i_class;


    temp_sort_list++;
  }
  qsort( (char *) sort_list, clsf->n_classes, sizeof( struct sort_cell), comp_func);

  temp_sort_list = sort_list;
  for (i_class=0; i_class<clsf->n_classes; i_class++) {
    class_weight_ordering[i_class] = temp_sort_list->int_value;


    temp_sort_list++;
  }

  free( sort_list);
  return (class_weight_ordering);
}
