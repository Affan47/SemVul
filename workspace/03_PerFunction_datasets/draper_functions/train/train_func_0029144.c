initMapData (GVJ_t* job, char* lbl, char* url, char* tooltip, char* target, char *id,
  void* gobj)
{
    obj_state_t *obj = job->obj;
    int flags = job->flags;
    int assigned = 0;

    if ((flags & GVRENDER_DOES_LABELS) && lbl)
        obj->label = lbl;
    if (flags & GVRENDER_DOES_MAPS) {
        obj->id = strdup_and_subst_obj(id, gobj);
	if (url && url[0]) {
            obj->url = strdup_and_subst_obj(url, gobj);
	    assigned = 1;
        }
    }
    if (flags & GVRENDER_DOES_TOOLTIPS) {
        if (tooltip && tooltip[0]) {
            obj->tooltip = strdup_and_subst_obj(tooltip, gobj);
            obj->explicit_tooltip = TRUE;
	    assigned = 1;
        }
        else if (obj->label) {
            obj->tooltip = strdup(obj->label);
	    assigned = 1;
        }
    }
    if ((flags & GVRENDER_DOES_TARGETS) && target && target[0]) {
        obj->target = strdup_and_subst_obj(target, gobj);
	assigned = 1;
    }
    return assigned;
}
