InitScreen ( int w, int h, int depth, Uint32 flags )
{
   bitsperpixel = depth;
   bool result = PG_Application::InitScreen ( w, h, depth, flags  );
   if ( result ) {
      initASCGraphicSubsystem ( GetScreen() );
      Surface::SetScreen( GetScreen() );

      fullScreen = flags & SDL_FULLSCREEN;

      MessagingHub::Instance().error.connect( SigC::bind( SigC::slot( *this, &ASC_PG_App:: messageDialog ), MessagingHubBase::Error ));
      MessagingHub::Instance().fatalError.connect( SigC::bind( SigC::slot( *this, &ASC_PG_App:: messageDialog ), MessagingHubBase::FatalError ));
      MessagingHub::Instance().warning.connect(SigC::bind( SigC::slot( *this, &ASC_PG_App:: messageDialog ), MessagingHubBase::Warning ));
      MessagingHub::Instance().infoMessage.connect( SigC::bind( SigC::slot( *this, &ASC_PG_App:: messageDialog ), MessagingHubBase::InfoMessage ));
   }

   return result;
}
