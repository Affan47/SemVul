createContextView( Plasma::Containment *containment )
{
    disconnect( m_corona.data(), SIGNAL(containmentAdded(Plasma::Containment*)),
            this, SLOT(createContextView(Plasma::Containment*)) );

    debug() << "Creating context view on containmend" << containment->name();
    PERF_LOG( "Creating ContexView" )
    m_contextView = new Context::ContextView( containment, m_corona.data(), m_mainWidget );
    m_contextView.data()->setFrameShape( QFrame::NoFrame );
    m_contextToolbarView = new Context::ToolbarView( containment, m_corona.data(), m_mainWidget );
    PERF_LOG( "Created ContexToolbarView" )

    connect( m_corona.data(), SIGNAL(sceneRectChanged(QRectF)), m_contextView.data(), SLOT(updateSceneRect(QRectF)) );
    connect( m_contextToolbarView.data(), SIGNAL(hideAppletExplorer()), m_contextView.data(), SLOT(hideAppletExplorer()) );
    connect( m_contextToolbarView.data(), SIGNAL(showAppletExplorer()), m_contextView.data(), SLOT(showAppletExplorer()) );
    m_contextView.data()->showHome();
    PERF_LOG( "ContexView created" )
}
