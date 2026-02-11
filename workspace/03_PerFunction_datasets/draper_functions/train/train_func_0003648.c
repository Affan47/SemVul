gvevent_refresh(GVJ_t * job)
{
    graph_t *g = job->gvc->g;

    if (!job->selected_obj) {
	job->selected_obj = g;
	GD_gui_state(g) |= GUI_STATE_SELECTED;
	gv_graph_state(job, g);
    }
    emit_graph(job, g);
    job->has_been_rendered = TRUE;
}
