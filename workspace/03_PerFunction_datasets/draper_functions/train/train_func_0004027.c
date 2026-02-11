Sequence_strncpy(Sequence *s, gint start, gint length, gchar *dst){
    register gint i;
    register gchar *str;
    register Sequence_Subseq *subseq;
    register SparseCache *cache;
    g_assert(start >= 0);
    g_assert(s->len > 0);
    g_assert(start < s->len);
    g_assert((start+length) <= s->len);

#if 0
    g_print("Sequence_strncpy [");
    Sequence_print_type(s);
    g_print("] [%d] [%d] [%s]\n", start, length, s->id);
#endif
    switch(s->type){
        case Sequence_Type_INTMEM:
            str = s->data;
            for(i = 0; i < length; i++)
                dst[i] = str[start+i];
            return;
        case Sequence_Type_EXTMEM:
            cache = s->data;
            SparseCache_copy(cache, start, length, dst);
            break;
        case Sequence_Type_SUBSEQ:
            subseq = s->data;
            Sequence_strncpy(subseq->sequence, start+subseq->start, length, dst);
            return;
        default:
            for(i = 0; i < length; i++)
                dst[i] = Sequence_get_symbol(s, start+i);
            break;
        }
    return;
    }
