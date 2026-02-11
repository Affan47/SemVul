run(ElementT *e, FILE *f)
{
    bool is_type = e->landmark() == type_landmark;
    String templ = _main_attrs[is_type ? "typeentry" : "entry"];
    run_template(templ, e, -1, false);
    fputs(_sa.c_str(), f);
    _sa.clear();
    _sep = _main_attrs["sep"];
}
