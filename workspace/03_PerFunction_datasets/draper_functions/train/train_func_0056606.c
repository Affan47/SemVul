fasta_chunk_write(FastaDB *fdb, CompoundFile_Pos start,
                              CompoundFile_Pos stop, gchar *path){
    register FILE *fp;
    register CompoundFile_Pos pos;
    if(start == stop)
        return;
    fp = fopen(path, "w");
    if(!fp)
        g_error("Could not open [%s] for writing fasta chunk", path);
    CompoundFile_seek(fdb->cf, start);
    for(pos = start; pos < stop; pos++)
        putc(CompoundFile_getc(fdb->cf), fp);
    fclose(fp);
    return;
    }
