get_last_commit_cancel_op() const
{
    CYG_REPORT_FUNCNAMETYPE("CdlTransaction::get_last_commit_cancel_op", "result %p");
    CYG_REPORT_FUNCARG1XV(this);
    CYG_PRECONDITION_THISC();

    CdlTransactionCommitCancelOp* op = *(commit_cancel_ops.rbegin());

    CYG_REPORT_RETVAL(op);
    return op;
}
