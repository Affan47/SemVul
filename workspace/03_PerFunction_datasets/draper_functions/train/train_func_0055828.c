pp_exit_profiler(pTHX)
{
    DB_leave(aTHX_ NULL, PL_op);
    if (PL_op->op_type == OP_EXEC)
        finish_profile(aTHX);
    return run_original_op(PL_op->op_type);
}
