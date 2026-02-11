onExecuteClicked()
{
    UT_DEBUGMSG(("onExecuteClicked() model1:%p\n", m_resultsModel ));
    UT_DEBUGMSG(("onExecuteClicked() model2:%p\n", gtk_tree_view_get_model( m_resultsView ) ));

    std::string q = tostr(GTK_TEXT_VIEW (m_query));
    executeQuery( q );
}
