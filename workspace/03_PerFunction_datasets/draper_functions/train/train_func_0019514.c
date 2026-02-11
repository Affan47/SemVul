cbf_compose_itemname (cbf_handle handle, const cbf_node *column, char * itemname, size_t limit)
    {

        cbf_node *category;

        char column_fill[1] = "\0";

        char * tempcat;

        char * tempcol;

        int ipos;

        itemname[0] = itemname[limit] = '\0';


        cbf_failnez (cbf_find_parent (&category, column, CBF_CATEGORY))


        if (!category->name && !column->name) {

            strncpy (itemname, "_(null)", limit );

            return CBF_ARGUMENT;

        }


        if (column->name) {

            tempcol = (char *)column->name;

        } else {

            tempcol = column_fill;
        }

        if (!category->name ||
            !(category->name[0]) ||
            !cbf_cistrcmp("(none)",category->name) ||
            tempcol[0]=='_') {

            strncpy(itemname,tempcol,limit);

            if (strlen(tempcol) > limit) return CBF_ARGUMENT;


        } else {

            if(!category->name) return CBF_ARGUMENT;

            itemname[0] = '_';

            cbf_failnez( cbf_require_category_root(handle,category->name,(const char **)&tempcat))

            strncpy(itemname+1,tempcat,limit-1);

            if (strlen(tempcat) > 72 || strlen(tempcat) > limit-1) return CBF_ARGUMENT;

            ipos = strlen(itemname);

            if ( ipos < limit ) itemname[ipos++] = '.';

            if ( limit-ipos > 0) strncpy(itemname+ipos,tempcol,limit-ipos);

            if (strlen(tempcol)+ipos+2 > 75 || strlen(tempcol)+ipos+2 > limit) return CBF_ARGUMENT;


        }

        return 0;

    }
