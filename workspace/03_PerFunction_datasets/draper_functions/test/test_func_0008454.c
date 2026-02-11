fs_query_group_block(fs_query *q, int b)
{

    if (rasqal_query_get_group_condition(q->rq, 0)) {
        for (int i=0; q->bb[b][i].name; i++) {
            q->bb[b][i].sort = 0;
        }
        fs_binding *gr = fs_binding_create(q->bb[b], "_group", FS_RID_NULL, 0);
        gr->bound = 1;
        gr->sort = 1;
        const long length = fs_binding_length(q->bb[b]);
        for (int i=0; rasqal_query_get_group_condition(q->rq, i); i++) {
            rasqal_expression *e = rasqal_query_get_group_condition(q->rq, i);

            for (long row = 0; row < length; row++) {
                fs_value v = fs_expression_eval(q, row, b, e);
                v = fs_value_fill_rid(q, v);


                if (i == 0) {
                    fs_rid_vector_append(gr->vals, v.rid);
                } else {

                    gr->vals->data[row] ^= (v.rid << i);
                }
            }
        }
        fs_binding_sort(q->bb[b]);
#ifdef DEBUG_MERGE
        printf("Grouped:\n");
        fs_binding_print(q->bb[b], stdout);
#endif
    }

    return 0;
}
