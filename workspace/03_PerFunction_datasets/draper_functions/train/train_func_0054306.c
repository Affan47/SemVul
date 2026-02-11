print_decl(ostream &out, string space, bool print_semi,
                        bool constraint_info, bool constrained)
{
    if (constrained && !send_p())
        return;

    out << space << type_name() << " {\n" ;
    for (Vars_citer i = d_vars.begin(); i != d_vars.end(); i++) {
        (*i)->print_decl(out, space + "    ", true, constraint_info, constrained);
    }
    out << space << "} " << id2www(name()) ;

    if (constraint_info) {
        if (send_p())
            out << ": Send True";
        else
            out << ": Send False";
    }

    if (print_semi)
        out << ";\n" ;
}
