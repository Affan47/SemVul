updateMenu( const QStringList &usedBreadcrumbLevels )
{

    foreach( QAction *action, m_menu->actions() )
        action->setEnabled( !usedBreadcrumbLevels.contains( action->data().toString() ) );
}

}
