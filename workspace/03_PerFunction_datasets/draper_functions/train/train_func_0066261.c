scm_s_lambda(ScmObj formals, ScmObj body, ScmObj env)
{
    DECLARE_FUNCTION("lambda", syntax_variadic_1);

#if SCM_STRICT_ARGCHECK
    if (SCM_LISTLEN_ERRORP(scm_validate_formals(formals)))
        ERR_OBJ("bad formals", formals);


#else


#endif


    if (!CONSP(body))
        ERR_OBJ(ERRMSG_EXPRESSION_REQUIRED, body);

    return MAKE_CLOSURE(CONS(formals, body), env);
}
