Dataset_write_seq_data(Dataset *dataset, FILE *fp){
    register gint i;
    register Dataset_Sequence *ds;
    for(i = 0; i < dataset->seq_list->len; i++){
        ds = dataset->seq_list->pdata[i];
        fprintf(fp, "%s%s%s\n",
                ds->id,
                ds->def?" ":"",
                ds->def?ds->def:"");
        }
    return;
    }
