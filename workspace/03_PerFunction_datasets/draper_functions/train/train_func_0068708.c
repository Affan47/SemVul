createModelMapper(QAbstractItemModel *model)
    {
        if (m_xmlOnly) {
            if (m_Mapper) {
                delete m_Mapper;
                m_Mapper = 0;
            }
            m_Model = 0;
            return;
        }
        m_xmlOnly = false;
        if (m_Mapper) {
            delete m_Mapper;
            m_Mapper = 0;
        }
        m_Mapper = new IsDirtyDataWidgetMapper(q);
        m_Mapper->setSubmitPolicy(IsDirtyDataWidgetMapper::ManualSubmit);
        m_Mapper->setModel(model);
        m_Model = model;
    }
