route_down_hierarchy(void **arg1, void **arg2, ED4_returncode (*function) (void **, void **, ED4_base *))
{
    int i;

    function(arg1, arg2, this);

    if (children) {
        for (i=0; i < children->members(); i++) {
            children->member(i)->route_down_hierarchy(arg1, arg2, function);
        }
    }

    return ED4_R_OK;
}
