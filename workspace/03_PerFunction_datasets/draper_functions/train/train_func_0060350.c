guard_handler(ScmObj q_condition, ScmEvalState *eval_state)
{
    ScmObj handler_body, ret;
    DECLARE_PRIVATE_FUNCTION("guard", syntax_fixed_tailrec_1);

    handler_body
        = scm_s_lambda(LIST_1(l_sym_handler_k),
                       LIST_1(LIST_2(l_syn_guard_handler_body, l_sym_handler_k)),
                       eval_state->env);
    ret = scm_call_with_current_continuation(handler_body, eval_state);
    ret = SCM_FINISH_TAILREC_CALL(ret, eval_state);
    return scm_call(ret, SCM_NULL);
}
