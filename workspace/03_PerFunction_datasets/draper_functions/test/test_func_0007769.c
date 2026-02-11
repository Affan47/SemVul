setModel( FractalModel* model )
{
    m_model = model;

    m_ui.listView->setColorSettings( model->gradient(), model->backgroundColor(), model->colorMapping() );

    m_presenter->setColorSettings( model->gradient(), model->backgroundColor(), model->colorMapping() );
    m_presenter->setGeneratorSettings( model->generatorSettings() );
    m_presenter->setViewSettings( model->viewSettings() );
}
