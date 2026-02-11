check_semantics(bool all)
{

    if (d_name == "") {
        cerr << "A dataset must have a d_name" << endl;
        return false;
    }

    string msg;
    if (!unique_names(vars, d_name, "Dataset", msg))
        return false;

    if (all)
        for (Vars_iter i = vars.begin(); i != vars.end(); i++)
            if (!(*i)->check_semantics(msg, true))
                return false;

    return true;
}
