mk_xaccess(Entry *ce, Section *cs ATTR_UNUSED)
{
    if (!ce->active)
        writeFile(def_Xaccess, 0644, def_xaccess);
    else if (old_confs)
        linkFile(ce);
    else
        copyFile(ce, 0644, 0);
}
