stack_from_project(project_ty *pp)
{
    stack = new string_list_ty();
    project_search_path_get(pp, stack, 1);


}
