assignment_op (parser_env_ptr pe)
{
    var_store_ptr vl;
    var_store_ptr vr;
    char ao;

    add_sub_op (pe);
    if (pe->error_code)
        return;

    while (pe->Token == ASN_OP)
    {
        vl = pop (pe);
        if (pe->error_code)
            return;

        ao = pe->asn_op;

        if (vl->variable_name)
        {
            next_token (pe);
            if (pe->error_code)
            {
                free_var (vl, pe);
                return;
            }

            assignment_op (pe);
            if (pe->error_code)
            {
                free_var (vl, pe);
                return;
            }

            vr = pop (pe);
            if (pe->error_code)
            {
                free_var (vl, pe);
                return;
            }

            vl->assign_flag = ASSIGNED_TO;

            if (ao)
            {
                void *temp;

                temp = vl->value;
                vl->value = pe->numeric_ops (ao, vl->value, vr->value);
                pe->free_numeric (temp);
            }
            else if (vl != vr)
            {
                if (!vr->variable_name)
                {
                    pe->free_numeric (vl->value);
                    vl->value = vr->value;
                    vr->value = NULL;
                }
                else
                {
                    pe->numeric_ops (ASN_OP, vl->value, vr->value);
                }

                free_var (vr, pe);
            }

            push (vl, pe);
        }
        else
        {
            add_token (pe, EOS);
            pe->error_code = NOT_A_VARIABLE;
            free_var (vl, pe);
        }
    }
}
