open()
{
#ifdef USE_EDS_CLIENT


    for (int retries = 0; retries < 2; retries++) {
        m_calendar.reset(E_CAL_CLIENT(openESource(sourceExtension(),
                                                  m_type == EVOLUTION_CAL_SOURCE_TYPE_EVENTS ? e_source_registry_ref_builtin_calendar :
                                                  m_type == EVOLUTION_CAL_SOURCE_TYPE_TASKS ? e_source_registry_ref_builtin_task_list :
                                                  m_type == EVOLUTION_CAL_SOURCE_TYPE_MEMOS ? e_source_registry_ref_builtin_memo_list :
                                                  NULL,
                                                  boost::bind(newECalClient,
                                                              _1,
                                                              sourceType(),
                                                              _2)).get()));
    }
#else
    GErrorCXX gerror;
    bool onlyIfExists = false;


    ESourceList *tmp;
    if (!e_cal_get_sources(&tmp, sourceType(), gerror)) {
        throwError("unable to access backend databases", gerror);
    }
    ESourceListCXX sources(tmp, TRANSFER_REF);

    string id = getDatabaseID();
    ESource *source = findSource(sources, id);
    bool created = false;


    for (int retries = 0; retries < 2; retries++) {
        if (!source) {


            if ((id.empty() || id == "<<system>>") && m_newSystem) {
                m_calendar.set(m_newSystem(), (string("system ") + m_typeName).c_str());
            } else if (!id.compare(0, 7, "file://")) {
                m_calendar.set(e_cal_new_from_uri(id.c_str(), sourceType()), (string("creating ") + m_typeName).c_str());
            } else {
                throwError(string("not found: '") + id + "'");
            }
            created = true;
            onlyIfExists = false;
        } else {
            m_calendar.set(e_cal_new(source, sourceType()), m_typeName.c_str());
        }

        e_cal_set_auth_func(m_calendar, eCalAuthFunc, this);

        if (!e_cal_open(m_calendar, onlyIfExists, gerror)) {
            if (created) {

                gerror.clear();
                sleep(5);
                if (!e_cal_open(m_calendar, onlyIfExists, gerror)) {
                    throwError(string("opening ") + m_typeName, gerror);
                }
            } else {
                throwError(string("opening ") + m_typeName, gerror);
            }
        }
    }

#endif

    g_signal_connect_after(m_calendar,
                           "backend-died",
                           G_CALLBACK(SyncContext::fatalError),
                           (void *)"Evolution Data Server has died unexpectedly, database no longer available.");
}
