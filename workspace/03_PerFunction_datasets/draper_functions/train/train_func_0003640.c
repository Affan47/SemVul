add_var(BaseType * v, Part)
{
#if 0
    if (v && v->is_dap4_only_type())
        throw InternalErr(__FILE__, __LINE__, "Attempt to add a DAP4 type to a DAP2 Vector.");
#endif

    if (_var) {
        delete _var;
        _var = 0;
    }


    if (!v) {
        _var = 0;
    }
    else {


        _var = v->ptr_duplicate();


        if (!v->name().empty())
            set_name(v->name());
        else
            _var->set_name(name());

        _var->set_parent(this);

        DBG(cerr << "Vector::add_var: Added variable " << v << " ("
                << v->name() << " " << v->type_name() << ")" << endl);
    }
}
