code_generate(stmt_ty *sp, opcode_list_ty *olp)
{
    stmt_recipe_ty  *this;
    stmt_result_ty  status;
    opcode_list_ty  *need1;
    opcode_list_ty  *need2;
    opcode_list_ty  *precondition;
    opcode_list_ty  *single_thread;
    opcode_list_ty  *host_binding;
    opcode_list_ty  *out_of_date;
    opcode_list_ty  *up_to_date;

    trace(("code_generate(sp = %08X)\n{\n", sp));
    assert(sp);
    this = (stmt_recipe_ty *)sp;
    status = STMT_OK;

    if (this->need.el_nexprs > 0)
    {
        need1 = opcode_list_new();
        opcode_list_append(need1, opcode_push_new());
        expr_list_code_generate(&this->need, need1);
    }
    else
        need1 = 0;

    if (this->need2.el_nexprs)
    {
        need2 = opcode_list_new();
        opcode_list_append(need2, opcode_push_new());
        expr_list_code_generate(&this->need2, need2);
    }
    else
        need2 = 0;

    if (this->precondition)
    {
        precondition = opcode_list_new();
        opcode_list_append(precondition, opcode_push_new());
        expr_code_generate(this->precondition, precondition);
    }
    else
        precondition = 0;

    if (this->single_thread.el_nexprs)
    {
        single_thread = opcode_list_new();
        opcode_list_append(single_thread, opcode_push_new());
        expr_list_code_generate(&this->single_thread, single_thread);
    }
    else
        single_thread = 0;

    if (this->host_binding.el_nexprs)
    {
        host_binding = opcode_list_new();
        opcode_list_append(host_binding, opcode_push_new());
        expr_list_code_generate(&this->host_binding, host_binding);
    }
    else
        host_binding = 0;


    out_of_date = 0;
    up_to_date = 0;
    if (this->action)
    {
        if (this->use_action)
        {
            stmt_ty         *sp2;
            stmt_list_ty    sl2;


            stmt_list_constructor(&sl2);
            stmt_list_append(&sl2, this->action);
            stmt_list_append(&sl2, this->use_action);
            sp2 = stmt_compound_new(&sl2);
            stmt_list_destructor(&sl2);


            out_of_date = stmt_compile(sp2);
            if (!out_of_date)
                status = STMT_ERROR;
            stmt_delete(sp2);


            up_to_date = stmt_compile(this->use_action);
            if (!up_to_date)
                status = STMT_ERROR;
        }
        else
        {


            out_of_date = stmt_compile(this->action);
            if (!out_of_date)
                status = STMT_ERROR;
        }
    }


    opcode_list_append(olp, opcode_push_new());
    expr_list_code_generate(&this->target, olp);


    opcode_list_append(olp, opcode_push_new());
    expr_list_code_generate(&this->flags, olp);


    opcode_list_append
    (
        olp,
        opcode_recipe_new
        (
            need1,
            need2,
            precondition,
            this->multiple,
            single_thread,
            host_binding,
            out_of_date,
            up_to_date,
            &this->position
        )
    );

    trace(("return %d;\n", status));
    trace(("}\n"));
    return status;
}
