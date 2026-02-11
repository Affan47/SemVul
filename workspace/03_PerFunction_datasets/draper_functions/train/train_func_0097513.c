tkgen_begin_graph(GVJ_t * job)
{
    obj_state_t *obj = job->obj;

    gvputs(job, "#");
    if (agnameof(obj->u.g)[0]) {
        gvputs(job, " Title: ");
	gvputs(job, tkgen_string(agnameof(obj->u.g)));
    }
    gvprintf(job, " Pages: %d\n", job->pagesArraySize.x * job->pagesArraySize.y);
}
