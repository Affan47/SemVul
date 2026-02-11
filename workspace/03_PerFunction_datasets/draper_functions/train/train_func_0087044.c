add_to_globals(vm_obj_id_t obj)
{
    CVmObjGlobPage *pg;


    if (get_entry(obj)->in_root_set_)
        return;


    if (globals_ != 0 && globals_->add_entry(obj))
    {

        return;
    }


    pg = new CVmObjGlobPage();
    pg->nxt_ = globals_;
    globals_ = pg;


    globals_->add_entry(obj);
}
