no(project_ty *pp, string_ty *name)
{
    return !project_administrator_query(pp, nstring(name));
}
