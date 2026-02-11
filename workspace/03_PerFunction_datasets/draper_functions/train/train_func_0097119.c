setRedoLimit(int limit) {
    if ( limit>0 && limit != d->m_redoLimit ) {
        d->m_redoLimit = limit;
        clipCommands();
    }
}
