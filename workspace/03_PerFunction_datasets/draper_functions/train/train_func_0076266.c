initialize(bool hideSelector)
{
    m_ui = new DrugsWidget::Internal::Ui::DrugsCentralWidget();
    m_ui->setupUi(this);


    m_Context = new Internal::DrugsContext(this);
    m_Context->setContext(Core::Context(Constants::C_DRUGS_PLUGINS));
    contextManager()->addContextObject(m_Context);


    m_CurrentDrugModel = new DrugsDB::DrugsModel(this);
    m_ui->m_PrescriptionView->initialize();
    m_ui->m_PrescriptionView->setModel(m_CurrentDrugModel);

    m_ui->m_DrugSelector->initialize();
    m_ui->m_DrugSelector->setFocus();
    if (hideSelector)
        m_ui->m_DrugSelector->hide();

    DrugsWidgetManager::instance()->setCurrentView(this);

    changeFontTo(QFont(settings()->value(Constants::S_VIEWFONT).toString(), settings()->value(Constants::S_VIEWFONTSIZE).toInt()));

    return true;
}
