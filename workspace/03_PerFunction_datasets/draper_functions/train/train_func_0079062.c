select_preset(Widget w, XtPointer list,
                          XtPointer call_data)
{
  XawListReturnStruct *ret;
  const struct cm_parameter *param;
  struct cm_parameter parameter;
  struct cm_result *result;


  fc_assert_ret(current_city != NULL);

  result = cm_result_new(current_city);
  ret = XawListShowCurrent(list);

  if (ret->list_index != XAW_LIST_NONE && cmafec_preset_num()) {
    param = cmafec_preset_get_parameter(ret->list_index);
    cmafec_set_fe_parameter(current_city, param);

    if (cma_is_city_under_agent(current_city, NULL)) {
      cma_release_city(current_city);
      cma_put_city_under_agent(current_city, param);
    }

    cmafec_get_fe_parameter(current_city, &parameter);
    cm_result_from_main_map(result, current_city);
    xaw_set_label(result_label,
        (char *) cmafec_get_result_descr(current_city, result, &parameter));

    output_type_iterate(i) {
      minimal_surplus[i] = param->minimal_surplus[i];
    } output_type_iterate_end;

    XtVaSetValues(celebrate_toggle, XtNlabel,
            param->require_happy ? _("Yes") : _("No"),
            XtNstate, parameter.require_happy, NULL);

    factors[O_LAST] = param->happy_factor;

    output_type_iterate(i) {
      factors[i] = param->factor[i];
    } output_type_iterate_end;
  }

  update_stat_labels(result->found_a_valid);
  cm_result_destroy(result);
}
