Optimize()
{
    for (std::vector<SymProc*>::const_iterator it = proc_decl_order.begin(); it != proc_decl_order.end(); ++it)
        (*it)->Optimize();
}
