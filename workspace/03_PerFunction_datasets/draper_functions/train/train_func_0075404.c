getDatabases()
{
    GErrorCXX gerror;
    Databases result;

#ifdef USE_EDS_CLIENT
    getDatabasesFromRegistry(result,
                             sourceExtension(),
                             m_type == EVOLUTION_CAL_SOURCE_TYPE_EVENTS ? e_source_registry_ref_default_calendar :
                             m_type == EVOLUTION_CAL_SOURCE_TYPE_TASKS ? e_source_registry_ref_default_task_list :
                             m_type == EVOLUTION_CAL_SOURCE_TYPE_MEMOS ? e_source_registry_ref_default_memo_list :
                             NULL);
#else
    ESourceList *tmp = NULL;
    if (!e_cal_get_sources(&tmp, sourceType(), gerror)) {


        if (!gerror) {
            tmp = NULL;
        } else {
            throwError("unable to access backend databases", gerror);
        }
    }
    ESourceListCXX sources(tmp, TRANSFER_REF);
    bool first = true;
    for (GSList *g = sources ? e_source_list_peek_groups (sources) : NULL;
         g;
         g = g->next) {
        ESourceGroup *group = E_SOURCE_GROUP (g->data);
        for (GSList *s = e_source_group_peek_sources (group); s; s = s->next) {
            ESource *source = E_SOURCE (s->data);
            eptr<char> uri(e_source_get_uri(source));
            result.push_back(Database(e_source_peek_name(source),
                                      uri ? uri.get() : "",
                                      first));
            first = false;
        }
    }
    if (result.empty() && m_newSystem) {
        eptr<ECal, GObject> calendar(m_newSystem());
        if (calendar.get()) {

            const char *uri = e_cal_get_uri(calendar.get());
            result.push_back(Database("<<system>>", uri ? uri : "<<unknown uri>>"));
        }
    }
#endif

    return result;
}
