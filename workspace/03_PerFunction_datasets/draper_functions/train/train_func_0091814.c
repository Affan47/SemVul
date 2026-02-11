ok()
      {
         if ( propertyEditor->Apply() ) {

            int x = vmodes.getx( videoMode );
            int y = vmodes.gety( videoMode );

            bool warn = false;
            bool fullscreen;


            if ( ascmain ) {
               if ( (x != CGameOptions::Instance()->xresolution || y != CGameOptions::Instance()->yresolution) && x && y  ) {
                  warn = true;
                  CGameOptions::Instance()->xresolution = x;
                  CGameOptions::Instance()->yresolution = y;
               }

               fullscreen = !CGameOptions::Instance()->forceWindowedMode;

            } else {
               if ( (x != CGameOptions::Instance()->mapeditor_xresolution || y != CGameOptions::Instance()->mapeditor_yresolution) && x && y ) {
                  warn = true;
                  CGameOptions::Instance()->mapeditor_xresolution = x;
                  CGameOptions::Instance()->mapeditor_yresolution = y;
               }
               fullscreen = !CGameOptions::Instance()->mapeditWindowedMode;
            }

            if ( warn )
               infoMessage( "The new graphic settings will be active after you restart ASC");

            if ( getPGApplication().isFullscreen() != fullscreen )
               getPGApplication().toggleFullscreen();


            CGameOptions::Instance()->setChanged();
            if ( !defaultPassword.empty() && defaultPassword.find_first_not_of('*') != ASCString::npos ) {
               Password p;
               p.setUnencoded ( defaultPassword );
               CGameOptions::Instance()->defaultPassword = p.toString();
            }

            quitModalLoop(0);

            return true;
         } else
            return false;
      }
