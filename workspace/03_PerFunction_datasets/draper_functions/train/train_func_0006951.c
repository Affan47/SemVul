getDockWidgetFromName( const QString& dockName )
{
  QObjectList::iterator it = childDock->begin();
  K3DockWidget * obj;
  while ( it != childDock->end() ) {
    obj=(K3DockWidget*)(*it);
    ++it;
    if ( obj->objectName() == dockName ) return obj;
  }

  K3DockWidget* autoCreate = 0L;
  if ( autoCreateDock ){
    kDebug(282)<<"Autocreating dock: "<<dockName;
    autoCreate = new K3DockWidget( this, dockName.toLatin1().constData(), QPixmap("") );
    autoCreateDock->append( autoCreate );
  }
  return autoCreate;
}
