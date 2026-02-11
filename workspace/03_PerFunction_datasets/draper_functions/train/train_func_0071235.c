sliders_scroll_callback(Widget w, XtPointer client_data,
                                    XtPointer position_val)
{
  int pos = XTPOINTER_TO_INT(position_val);
  struct cm_parameter parameter;
  struct cm_result *result;
  int i, preset_index;


  fc_assert_ret(current_city != NULL);

  result = cm_result_new(current_city);

  output_type_iterate(i) {
    if (w == surplus_slider[i]) {
      if (pos > 0 ) {
        minimal_surplus[i]++;
        if (minimal_surplus[i] == 21) {
          minimal_surplus[i]--;
        }
      } else {
        minimal_surplus[i]--;
        if (minimal_surplus[i] == -21) {
          minimal_surplus[i]++;
        }
      }
    }
  } output_type_iterate_end;

  for (i = 0; i < (O_LAST + 1); i++) {
    if (w == factor_slider[i]) {
      if (pos > 0 ) {
        factors[i]++;
        if (factors[i] == 26) {
          factors[i]--;
        }
      } else {
        factors[i]--;
        if (factors[i] == 0) {
          factors[i]++;
        }
      }
    }
  }

  cmafec_get_fe_parameter(current_city, &parameter);

  output_type_iterate(i) {
    parameter.minimal_surplus[i] = minimal_surplus[i];
    parameter.factor[i] = factors[i];
  } output_type_iterate_end;

  XtVaGetValues(celebrate_toggle, XtNstate, &parameter.require_happy, NULL);
  parameter.happy_factor = factors[O_LAST];

  cmafec_set_fe_parameter(current_city, &parameter);

  if (cma_is_city_under_agent(current_city, NULL)) {
    cma_release_city(current_city);
    cma_put_city_under_agent(current_city, &parameter);
  }

  cmafec_get_fe_parameter(current_city, &parameter);
  cm_result_from_main_map(result, current_city);
  xaw_set_label(result_label,
        (char *) cmafec_get_result_descr(current_city, result, &parameter));

  update_stat_labels(result->found_a_valid);
  update_cma_preset_list();


  preset_index = cmafec_preset_get_index_of_parameter(&parameter);
  if (preset_index != -1) {
    XawListHighlight(preset_list, preset_index);
  }

  cm_result_destroy(result);
}
