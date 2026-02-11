jl_type_infer(jl_lambda_info_t *li, jl_tuple_t *argtypes,
                   jl_lambda_info_t *def)
{
    int last_ii = jl_in_inference;
    jl_in_inference = 1;
    if (jl_typeinf_func != NULL) {


        assert(li->inInference == 0);
        li->inInference = 1;
        jl_value_t *fargs[4];
        fargs[0] = (jl_value_t*)li;
        fargs[1] = (jl_value_t*)argtypes;
        fargs[2] = (jl_value_t*)jl_null;
        fargs[3] = (jl_value_t*)def;
#ifdef TRACE_INFERENCE
        ios_printf(ios_stderr,"inference on %s(", li->name->name);
        print_sig(argtypes);
        ios_printf(ios_stderr, ")\n");
#endif
#ifdef ENABLE_INFERENCE
        jl_value_t *newast = jl_apply(jl_typeinf_func, fargs, 4);
        li->ast = jl_tupleref(newast, 0);
        li->inferred = jl_true;
#endif
        li->inInference = 0;
    }
    jl_in_inference = last_ii;
}
