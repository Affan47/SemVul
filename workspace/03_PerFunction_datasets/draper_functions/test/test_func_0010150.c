grab()
    const
{


    trace(("rpt_value_pconf::grab(this = %08lX)\n{\n", (long)this));
    assert(!value);
    assert(cp);
    pconf_ty *pconf_data = change_pconf_get(cp, 0);


    value = pconf_type.convert(&pconf_data);
    assert(value);
    assert(dynamic_cast<rpt_value_struct *>(value.get()));

    trace(("value = %08lX;\n", (long)value.get()));
    trace(("}\n"));
}
