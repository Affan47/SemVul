fasta_index_fetch(FastaDB *fdb, FILE *index_fp,
                               FastaDB_Mask mask, gchar *id,
                               gboolean be_silent){
    register CompoundFile_Pos pos = fasta_index_lookup(fdb,
                                                       index_fp, id);
    register FastaDB_Seq *fdbs;
    if(pos == -1){
        if(be_silent)
            return NULL;
        g_error("Could not find identifier [%s] (missing -F ?)", id);
        }
    fdbs = FastaDB_fetch(fdb, mask, pos);
    g_assert(!strcmp(fdbs->seq->id, id));
    return fdbs;
    }
