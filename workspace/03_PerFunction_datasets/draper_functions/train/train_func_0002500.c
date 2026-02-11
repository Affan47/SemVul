graph_build(graph_ty *gp, string_ty *target,
    graph_build_preference_ty preference, int waffle)
{
    graph_build_result_ty result;

    graph_build_file(gp, target, preference, &result, 1);
    if
    (
        result.status == graph_build_status_backtrack
    &&
        preference == graph_build_preference_error
    )
        return graph_build_status_error;
    if (result.status == graph_build_status_success)
    {
        assert(result.gfp);
        if (waffle)
            result.gfp->primary_target = 1;
    }
    return result.status;
}
