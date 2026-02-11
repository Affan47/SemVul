Scm_DefineReaderCtor(ScmObj symbol, ScmObj proc, ScmObj finisher,
                            ScmObj module )
{
    ScmObj pair;
    if (!SCM_PROCEDUREP(proc)) {
        Scm_Error("procedure required, but got %S\n", proc);
    }
    pair = Scm_Cons(proc, finisher);
    (void)SCM_INTERNAL_MUTEX_LOCK(readCtorData.mutex);
    Scm_HashTableSet(readCtorData.table, symbol, pair, 0);
    (void)SCM_INTERNAL_MUTEX_UNLOCK(readCtorData.mutex);
    return SCM_UNDEFINED;
}
