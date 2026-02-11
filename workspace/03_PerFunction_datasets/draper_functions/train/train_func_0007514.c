execute(const opcode_ty *op, opcode_context_ty *icp)
{
    const opcode_recipe_ty *this;
    opcode_status_ty status;
    string_list_ty  *target;
    recipe_ty       *rp;
    string_list_ty  *flags_words;
    flag_ty         *flags;

    trace(("opcode_recipe::execute()\n{\n"));
    this = (const opcode_recipe_ty *)op;
    flags = 0;
    status = opcode_status_success;
    flags_words = opcode_context_string_list_pop(icp);
    target = opcode_context_string_list_pop(icp);

    if (target->nstrings == 0)
    {
        error_with_position
        (
            &this->pos,
            0,
            i18n("attempt to instantiate recipe with no targets")
        );
        status = opcode_status_error;
        goto done;
    }
    else if (target->nstrings > 1 && this->multiple && this->out_of_date)
    {
        error_with_position
        (
            &this->pos,
            0,
            i18n("double-colon recipes with multiple targets are not permitted")
        );
        status = opcode_status_error;
        goto done;
    }


    flags = flag_recognize(flags_words, &this->pos);
    if (!flags)
    {
        status = opcode_status_error;
        goto done;
    }


    rp =
        recipe_new
        (
            target,
            this->need1,
            this->need2,
            flags,
            this->multiple,
            this->precondition,
            this->single_thread,
            this->host_binding,
            this->out_of_date,
            this->up_to_date,
            &this->pos
        );
    if (!rp)
    {


        status = opcode_status_error;
        goto done;
    }


    if (rp->implicit)
        cook_implicit_append(rp);
    else
        cook_explicit_append(rp);


    if (option_test(OPTION_REASON))
    {
        if (rp->implicit)
        {
            error_with_position
            (
                &this->pos,
                0,
                i18n("implicit recipe instantiated (reason)")
            );
        }
        else
        {
            error_with_position
            (
                &this->pos,
                0,
                i18n("explicit recipe instantiated (reason)")
            );
        }
    }
    recipe_delete(rp);

  done:
    if (flags)
        flag_delete(flags);
    string_list_delete(target);
    string_list_delete(flags_words);
    trace(("return %s;\n", opcode_status_name(status)));
    trace(("}\n"));
    return status;
}
