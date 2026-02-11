_elm_gengrid_smart_add(Evas_Object *obj)
{
   Eina_Bool bounce = _elm_config->thumbscroll_bounce_enable;
   Elm_Gengrid_Pan_Smart_Data *pan_data;

   EVAS_SMART_DATA_ALLOC(obj, Elm_Gengrid_Smart_Data);

   ELM_WIDGET_CLASS(_elm_gengrid_parent_sc)->base.add(obj);

   priv->hit_rect = evas_object_rectangle_add(evas_object_evas_get(obj));
   evas_object_smart_member_add(priv->hit_rect, obj);
   elm_widget_sub_object_add(obj, priv->hit_rect);


   evas_object_color_set(priv->hit_rect, 0, 0, 0, 0);
   evas_object_show(priv->hit_rect);
   evas_object_repeat_events_set(priv->hit_rect, EINA_TRUE);

   elm_widget_can_focus_set(obj, EINA_TRUE);

   priv->calc_cb = (Ecore_Cb)_calc_job;

   priv->generation = 1;

   elm_layout_theme_set(obj, "gengrid", "base", elm_widget_style_get(obj));


   priv->s_iface = evas_object_smart_interface_get
       (obj, ELM_SCROLLABLE_IFACE_NAME);

   priv->s_iface->objects_set
     (obj, ELM_WIDGET_DATA(priv)->resize_obj, priv->hit_rect);

   priv->old_h_bounce = bounce;
   priv->old_v_bounce = bounce;
   priv->s_iface->bounce_allow_set(obj, bounce, bounce);

   priv->s_iface->animate_start_cb_set(obj, _scroll_animate_start_cb);
   priv->s_iface->animate_stop_cb_set(obj, _scroll_animate_stop_cb);
   priv->s_iface->drag_start_cb_set(obj, _scroll_drag_start_cb);
   priv->s_iface->drag_stop_cb_set(obj, _scroll_drag_stop_cb);
   priv->s_iface->edge_left_cb_set(obj, _edge_left_cb);
   priv->s_iface->edge_right_cb_set(obj, _edge_right_cb);
   priv->s_iface->edge_top_cb_set(obj, _edge_top_cb);
   priv->s_iface->edge_bottom_cb_set(obj, _edge_bottom_cb);
   priv->s_iface->scroll_cb_set(obj, _scroll_cb);

   priv->align_x = 0.5;
   priv->align_y = 0.5;
   priv->highlight = EINA_TRUE;

   priv->pan_obj = evas_object_smart_add
       (evas_object_evas_get(obj), _elm_gengrid_pan_smart_class_new());
   pan_data = evas_object_smart_data_get(priv->pan_obj);
   pan_data->wsd = priv;

   priv->s_iface->extern_pan_set(obj, priv->pan_obj);
}
