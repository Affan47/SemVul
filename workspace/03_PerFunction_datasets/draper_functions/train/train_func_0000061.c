options_add_filter(obj_list_t *obj_list,
                       int n_objs,
                       filter_info_t filt,
                       pack_opttbl_t *table )
{

    unsigned int i, I;
    int          j, added=0, found=0;


    if (table->nelems+n_objs >= table->size)
    {
        if (aux_inctable(table,n_objs)<0)
            return -1;
    }


    if (table->nelems>0)
    {

        for (j = 0; j < n_objs; j++)
        {

            for (i = 0; i < table->nelems; i++)
            {

                if (HDstrcmp(obj_list[j].obj,table->objs[i].path)==0)
                {

                    aux_tblinsert_filter(table,i,filt);
                    found=1;
                    break;
                }
            }

            if (found==0)
            {

                I = table->nelems + added;
                added++;
                HDstrcpy(table->objs[I].path,obj_list[j].obj);
                aux_tblinsert_filter(table,I,filt);
            }


            else if (found==1 && HDstrcmp(obj_list[j].obj,table->objs[i].path)!=0)
            {

                I = table->nelems + added;
                added++;
                HDstrcpy(table->objs[I].path,obj_list[j].obj);
                aux_tblinsert_filter(table,I,filt);
            }
        }
    }


    else
    {

        for (j = 0; j < n_objs; j++)
        {
            I = table->nelems + added;
            added++;
            HDstrcpy(table->objs[I].path,obj_list[j].obj);
            aux_tblinsert_filter(table,I,filt);
        }
    }

    table->nelems+= added;

    return 0;
}
