evaluate(string_ty *path_unres, string_ty *path,
    string_ty *path_res, struct stat *st) const
{


    trace(("mod::evaluate()\n"));
    rpt_value::pointer v1 =
        get_left()->evaluate(path_unres, path, path_res, st);
    if (v1->is_an_error())
    {
	trace(("}\n"));
	return v1;
    }


    rpt_value::pointer v1a = rpt_value::arithmetic(v1);


    rpt_value::pointer v2 =
        get_right()->evaluate(path_unres, path, path_res, st);
    if (v2->is_an_error())
    {
	trace(("}\n"));
	return v2;
    }


    rpt_value::pointer v2a = rpt_value::arithmetic(v2);


    rpt_value_integer *v1a_ip = dynamic_cast<rpt_value_integer *>(v1a.get());
    if (v1a_ip)
    {
        long num = v1a_ip->query();

        rpt_value_integer *v2a_ip =
            dynamic_cast<rpt_value_integer *>(v2a.get());
        if (v2a_ip)
        {
            long den = v2a_ip->query();
            if (den == 0)
                return modulo_by_zero_error();
            return rpt_value_integer::create(num % den);
        }

        rpt_value_real *v2a_rp = dynamic_cast<rpt_value_real *>(v2a.get());
        if (v2a_rp)
        {
            double den = v2a_rp->query();
            if (den == 0)
                return modulo_by_zero_error();
            return rpt_value_real::create(fmod(num, den));
        }
    }

    rpt_value_real *v1a_rp = dynamic_cast<rpt_value_real *>(v1a.get());
    if (v1a_rp)
    {
        double num = v1a_rp->query();

        rpt_value_integer *v2a_ip =
            dynamic_cast<rpt_value_integer *>(v2a.get());
        if (v2a_ip)
        {
            long den = v2a_ip->query();
            if (den == 0)
                return modulo_by_zero_error();
            return rpt_value_real::create(fmod(num, den));
        }

        rpt_value_real *v2a_rp = dynamic_cast<rpt_value_real *>(v2a.get());
        if (v2a_rp)
        {
            double den = v2a_rp->query();
            if (den == 0)
                return modulo_by_zero_error();
            return rpt_value_real::create(fmod(num, den));
        }
    }

    sub_context_ty sc;
    sc.var_set_charstar("Name1", v1a->name());
    sc.var_set_charstar("Name2", v2a->name());

    nstring s(sc.subst_intl(i18n("illegal modulo ($name1 % $name2)")));
    return rpt_value_error::create(s);
}
