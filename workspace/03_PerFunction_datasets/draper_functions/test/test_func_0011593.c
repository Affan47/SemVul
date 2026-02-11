hdiff_list (const char* fname,
                   dtable_t *table,
                   diff_dim_table_t *td1,
                   diff_dim_table_t *td2,
                   int *err)
{
    int32    file_id=-1,
             sd_id=-1,
             gr_id=-1;


    if ((file_id  = Hopen (fname,DFACC_READ,(int16)0))==FAIL)
    {
        printf("Cannot open file <%s>\n",fname);
        goto out;
    }


    if ((sd_id  = SDstart (fname, DFACC_READ))==FAIL)
    {
        printf( "Could not start SD for <%s>\n",fname);
        goto out;
    }


    if ((gr_id  = GRstart (file_id))==FAIL)
    {
        printf( "Could not start GR for <%s>\n",fname);
        goto out;
    }


    if ( hdiff_list_vg (fname,file_id,sd_id,gr_id,table,td1,td2) < 0)
        goto out;
    if ( hdiff_list_gr (file_id,gr_id,table) < 0)
        goto out;
    if ( hdiff_list_sds(file_id,sd_id,table,td1,td2) < 0)
        goto out;
    if ( hdiff_list_vs (file_id,table) < 0)
        goto out;
    if ( hdiff_list_glb(sd_id,gr_id) < 0)
        goto out;
    if ( hdiff_list_an (file_id) < 0)
        goto out;


    if (GRend (gr_id)==FAIL)
    {
        printf( "Failed to close GR interface <%s>\n", fname);
        goto out;
    }
    if (SDend (sd_id)==FAIL)
    {
        printf( "Failed to close SD interface <%s>\n", fname);
        goto out;
    }
    if (Hclose (file_id) == FAIL )
    {
        printf( "Failed to close file <%s>\n", fname);
        goto out;
    }

    *err=0;
    return table->nobjs;

out:

    if (sd_id!=-1)
        SDend(sd_id);
    if (gr_id!=-1)
        GRend(gr_id);
    if (file_id!=-1)
        Hclose(file_id);

    *err=1;
    return 0;
}
