FastaDB_rewind(FastaDB *fdb){
    register gint ch, prev = '\n';
    g_assert(fdb);
    CompoundFile_rewind(fdb->cf);
    while((ch = CompoundFile_getc(fdb->cf)) != EOF){
        if((ch == '>') && (prev == '\n'))
            break;
        prev = ch;
        }
    return;
    }
