test_ser_r_Caemtables_destroy (yyscan_t yyscanner)
{
    struct yytbl_dmap *dmap=0;

    if(!0){

        for(dmap=yydmap; dmap->dm_id; dmap++) {
            void * v;
            v = dmap->dm_arr;
            if(v && *(char**)v){
                    test_ser_r_Caemfree(*(char**)v ,yyscanner);
                    *(char**)v = NULL;
            }
        }
    }

    return 0;
}
