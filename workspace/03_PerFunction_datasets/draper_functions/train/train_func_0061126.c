ProcessEvent ( const SDL_Event *   event,bool   bModal = false  ) {


         if ( mainScreenWidget && mainScreenWidget->getUnitInfoPanel() )
            if ( mainScreenWidget->getUnitInfoPanel()->ProcessEvent( event, bModal ))
               return true;

         if ( mainScreenWidget && mainScreenWidget->getGuiHost() )
            if ( mainScreenWidget->getGuiHost()->ProcessEvent( event, bModal ))
               return true;

         if ( Panel::ProcessEvent( event, bModal ))
            return true;

         return false;
      }
