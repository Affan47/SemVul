FastaDB_Key_get_def(FastaDB_Key *fdbk){
    register gint ch;
    register gchar *def = NULL;
    register GString *s;
#ifdef USE_PTHREADS
    pthread_mutex_lock(&fdbk->source->cf->compoundfile_mutex);
#endif
    CompoundFile_Location_seek(fdbk->location);
    while((ch = CompoundFile_getc(fdbk->source->cf)) != EOF)
        if((ch == '\n') || (ch == ' ') || (ch == '\t'))
            break;
    if(ch == '\n'){
#ifdef USE_PTHREADS
        pthread_mutex_unlock(&fdbk->source->cf->compoundfile_mutex);
#endif
        return NULL;
        }
    s = g_string_sized_new(64);
    while((ch = CompoundFile_getc(fdbk->source->cf)) != EOF){
        if(ch == '\n')
            break;
        s = g_string_append_c(s, ch);
        }
#ifdef USE_PTHREADS
    pthread_mutex_unlock(&fdbk->source->cf->compoundfile_mutex);
#endif
    def = s->str;
    g_string_free(s, FALSE);
    return def;
    }
