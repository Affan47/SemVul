activate()
{
  K3DockWidget * obj;
  foreach ( QObject *o, *childDock ) {
  	obj=(K3DockWidget*)o;
    if ( obj->widget ) obj->widget->show();
    if ( !obj->parentDockTabGroup() ){
        obj->show();
    }
  }
  if ( !main->inherits("QDialog") ) main->show();
}
