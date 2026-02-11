userHandler( const ASCString& label, PropertyReadingContainer& pc, PG_Widget* parent, WidgetParameters widgetParams )
{
   if ( label == "FileList" ) {
      FileSelectionItemFactory* factory = new FileSelectionItemFactory( mapextension );
      factory->filenameSelectedKeyb.connect ( SigC::slot( *this, &StartMultiplayerGame::fileNameSelected ));
      factory->filenameSelectedMouse.connect ( SigC::slot( *this, &StartMultiplayerGame::fileNameMarked ));
      factory->filenameMarked.connect   ( SigC::slot( *this, &StartMultiplayerGame::fileNameMarked ));
      new ItemSelectorWidget( parent, PG_Rect(0, 0, parent->Width(), parent->Height()), factory );
   }

   if ( label == "PlayerSetup" )
      playerSetupParent = parent;

   if ( label == "AllianceSetup" )
      allianceSetupParent = parent;

   if ( label == "GameParameters" )
      mapParameterEditorParent = parent;

   if ( label == "EmailSetup" )
      emailSetupParent = parent;

}
