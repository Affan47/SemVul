emit_edge_label(GVJ_t* job, textlabel_t* lbl, emit_state_t lkind, int explicit,
    char* url, char* tooltip, char* target, char *id, splines* spl)
{
    int flags = job->flags;
    emit_state_t old_emit_state;
    char* newid;
    char* type;

    if ((lbl == NULL) || !(lbl->set)) return;
    if (id) {
	newid = N_NEW(strlen(id) + sizeof("-headlabel"),char);
	switch (lkind) {
	case EMIT_ELABEL :
	    type = "label";
	    break;
	case EMIT_HLABEL :
	    type = "headlabel";
	    break;
	case EMIT_TLABEL :
	    type = "taillabel";
	    break;
	default :
	    assert (0);
	    break;
	}
	sprintf (newid, "%s-%s", id, type);
    }
    else
	newid = NULL;
    old_emit_state = job->obj->emit_state;
    job->obj->emit_state = lkind;
    if ((url || explicit) && !(flags & EMIT_CLUSTERS_LAST)) {
	map_label(job, lbl);
	gvrender_begin_anchor(job, url, tooltip, target, newid);
    }
    emit_label(job, lkind, lbl);
    if (spl) emit_attachment(job, lbl, spl);
    if (url || explicit) {
	if (flags & EMIT_CLUSTERS_LAST) {
	    map_label(job, lbl);
	    gvrender_begin_anchor(job, url, tooltip, target, newid);
	}
	gvrender_end_anchor(job);
    }
    if (newid) free (newid);
    job->obj->emit_state = old_emit_state;
}
