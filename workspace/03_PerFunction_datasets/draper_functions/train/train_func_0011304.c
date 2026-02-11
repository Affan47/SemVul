gl3_content_get(void *data, Evas_Object *obj, const char *part)
{
   const Testitem *tit = data;
   if (!strcmp(part, "elm.swallow.icon"))
     {
        Evas_Object *lb;

        lb = elm_label_add(obj);
        elm_label_line_wrap_set(lb, ELM_WRAP_CHAR);
        elm_label_wrap_width_set(lb, 201);
        elm_object_text_set(lb, "ashj ascjscjh n asjkl hcjlh ls hzshnn zjh sh zxjcjsnd h dfw sdv edev efe fwefvv vsd cvs ws wf  fvwf wd fwe f  we wef we wfe rfwewef wfv wswf wefg sdfws w wsdcfwcf wsc vdv  sdsd sdcd cv wsc sdcv wsc d sdcdcsd sdcdsc wdvd sdcsd wscxcv wssvd sd");
        return lb;
     }
   else if (!strcmp(part, "elm.swallow.end"))
     {
        Evas_Object *ck;
        ck = elm_check_add(obj);
        evas_object_propagate_events_set(ck, EINA_FALSE);
        elm_check_state_set(ck, tit->onoff);
        evas_object_smart_callback_add(ck, "changed", my_gl_item_check_changed, data);
        return ck;
     }
   return NULL;
}
