fasta_explode_traverse_func(FastaDB_Seq *fdbs,
                                            gpointer user_data){
    register gchar *dir_path = user_data;
    register gchar *output_path = g_strconcat(dir_path,
        G_DIR_SEPARATOR_S, fdbs->seq->id, ".fa", NULL);
    register FILE *fp = fopen(output_path, "r");
    if(fp){
        fclose(fp);
        g_error("File [%s] already exists", output_path);
        }
    fp = fopen(output_path, "w");
    if(!fp)
        g_error("Could not open [%s] to write output", output_path);
    FastaDB_Seq_print(fdbs, fp, FastaDB_Mask_ID
                               |FastaDB_Mask_DEF
                               |FastaDB_Mask_SEQ);
    g_free(output_path);
    fclose(fp);
    return FALSE;
    }
