setBuddy( QAction* buddy )
{
  d->buddy = buddy;

  QList<QLabel*> labels;
  foreach ( QWidget* widget, associatedWidgets() )
    if ( QToolBar* toolBar = qobject_cast<QToolBar*>( widget ) )
      if ( QLabel* label = qobject_cast<QLabel*>( toolBar->widgetForAction( this ) ) )
        labels.append( label );

  foreach ( QWidget* widget, buddy->associatedWidgets() )
    if ( QToolBar* toolBar = qobject_cast<QToolBar*>( widget ) ) {
      QWidget* newBuddy = toolBar->widgetForAction( buddy );
      foreach ( QLabel* label, labels )
        label->setBuddy( newBuddy );
      return;
    }
}
