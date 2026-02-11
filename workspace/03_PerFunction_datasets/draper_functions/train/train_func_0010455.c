title_set(const nstring &arg)
{
    nstring projname(project_name_get(project));
    title = "Project " + projname + ", " + arg.capitalize();
}
