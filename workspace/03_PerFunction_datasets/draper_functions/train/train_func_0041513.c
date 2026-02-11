commit(CdlTransaction transaction)
    {
        CYG_PRECONDITION_CLASSC(package);
        CdlLoadableBody::transaction_commit_unload(transaction, package);
        package = 0;
    }
