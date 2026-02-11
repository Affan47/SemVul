test_genlist17(void *data __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Evas_Object *win, *fr1, *fr2, *bx, *bx2, *rdg = NULL, *gl;
   int i;
   static Testitem tit[50];

   win = elm_win_util_standard_add("genlist-decorate-modes", "Genlist Decorate Modes");
   elm_win_autodel_set(win, EINA_TRUE);

   bx = elm_box_add(win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   elm_win_resize_object_add(win, bx);
   evas_object_show(bx);

   bx2 = elm_box_add(win);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_horizontal_set(bx2, EINA_TRUE);
   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   fr1 = _decorate_item_mode_frame_new(win, &rdg);
   elm_box_pack_end(bx2, fr1);

   gl = elm_genlist_add(win);
   evas_object_size_hint_align_set(gl, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_size_hint_weight_set(gl, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_smart_callback_add(gl, "drag,start,right", _my_gl_mode_right, rdg);
   evas_object_smart_callback_add(gl, "drag,start,left", _my_gl_mode_left, rdg);
   evas_object_smart_callback_add(gl, "drag,start,up", _my_gl_mode_cancel, rdg);
   evas_object_smart_callback_add(gl, "drag,start,down", _my_gl_mode_cancel, rdg);
   evas_object_show(gl);

   itc17 = elm_genlist_item_class_new();
   itc17->item_style     = "default";
   itc17->decorate_item_style = "mode";
   itc17->func.text_get = gl15_text_get;
   itc17->func.content_get  = gl15_content_get;
   itc17->func.state_get = gl_state_get;
   itc17->func.del       = NULL;
   itc17->decorate_all_item_style = "edit";

   for (i = 0; i < 50; i++)
     {
        tit[i].checked = EINA_FALSE;
        tit[i].mode = i;
        tit[i].item = elm_genlist_item_append(gl,
                                              itc17,
                                              &(tit[i]),
                                              NULL,
                                              ELM_GENLIST_ITEM_NONE,
                                              NULL,
                                              NULL);
     }

   elm_genlist_item_class_free(itc17);
   elm_box_pack_end(bx, gl);

   fr2 = _decorate_all_mode_frame_new(win, rdg, gl);
   elm_box_pack_end(bx2, fr2);

   evas_object_resize(win, 520, 520);
   evas_object_show(win);
}
