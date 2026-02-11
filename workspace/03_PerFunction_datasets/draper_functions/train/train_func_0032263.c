dataset_constraint(DDS & dds, ConstraintEvaluator & eval,
                               ostream &out, bool ce_eval) const
{

    dds.print_constrained(out);
    out << "Data:\n" ;
    out << flush ;


    XDRStreamMarshaller m( out ) ;

    try {

        for (DDS::Vars_iter i = dds.var_begin(); i != dds.var_end(); i++)
            if ((*i)->send_p()) {
                DBG(cerr << "Sending " << (*i)->name() << endl);
                (*i)->serialize(eval, dds, m, ce_eval);
            }
    }
    catch (Error & e) {
        throw;
    }
}
