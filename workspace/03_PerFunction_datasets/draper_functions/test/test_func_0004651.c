_elm_scroller_smart_add(Evas_Object *obj)
{
   Evas_Coord minw, minh;

   EVAS_SMART_DATA_ALLOC(obj, Elm_Scroller_Smart_Data);

   ELM_WIDGET_CLASS(_elm_scroller_parent_sc)->base.add(obj);

   elm_widget_can_focus_set(obj, EINA_TRUE);

   elm_layout_theme_set(obj, "scroller", "base", elm_widget_style_get(obj));

   priv->hit_rect = evas_object_rectangle_add(evas_object_evas_get(obj));
   evas_object_smart_member_add(priv->hit_rect, obj);
   elm_widget_sub_object_add(obj, priv->hit_rect);

   evas_object_color_set(priv->hit_rect, 0, 0, 0, 0);
   evas_object_show(priv->hit_rect);
   evas_object_repeat_events_set(priv->hit_rect, EINA_TRUE);


   elm_widget_focus_region_hook_set(obj, _focus_region_hook);

   priv->s_iface = evas_object_smart_interface_get
       (obj, ELM_SCROLLABLE_IFACE_NAME);

   priv->s_iface->objects_set
     (obj, ELM_WIDGET_DATA(priv)->resize_obj, priv->hit_rect);

   evas_object_event_callback_add
     (obj, EVAS_CALLBACK_CHANGED_SIZE_HINTS, _changed_size_hints_cb, obj);

   edje_object_size_min_calc(ELM_WIDGET_DATA(priv)->resize_obj, &minw, &minh);
   evas_object_size_hint_min_set(obj, minw, minh);
   evas_object_event_callback_add(obj, EVAS_CALLBACK_RESIZE, _resize_cb, obj);

   priv->s_iface->edge_left_cb_set(obj, _edge_left_cb);
   priv->s_iface->edge_right_cb_set(obj, _edge_right_cb);
   priv->s_iface->edge_top_cb_set(obj, _edge_top_cb);
   priv->s_iface->edge_bottom_cb_set(obj, _edge_bottom_cb);
   priv->s_iface->scroll_cb_set(obj, _scroll_cb);
   priv->s_iface->animate_start_cb_set(obj, _scroll_anim_start_cb);
   priv->s_iface->animate_stop_cb_set(obj, _scroll_anim_stop_cb);
   priv->s_iface->drag_start_cb_set(obj, _scroll_drag_start_cb);
   priv->s_iface->drag_stop_cb_set(obj, _scroll_drag_stop_cb);

   priv->s_iface->content_min_limit_cb_set
     (obj, _elm_scroller_content_min_limit_cb);
}
