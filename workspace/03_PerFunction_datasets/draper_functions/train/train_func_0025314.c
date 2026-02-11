safe_eval_thunk(ScmObj *args, int nargs, void *data)
{
    struct eval_packet_rec *epak = (struct eval_packet_rec*)data;

    switch (epak->kind) {
    case SAFE_EVAL_CSTRING:
        return Scm_VMEval(Scm_ReadFromCString(epak->cstr), epak->env);
    case SAFE_EVAL:
        return Scm_VMEval(epak->arg0, epak->env);
    case SAFE_APPLY:
        return Scm_VMApply(epak->arg0, epak->args);
    default:
        Scm_Panic("safe_eval_subr: bad kind");
        return SCM_UNBOUND;
    }
}
