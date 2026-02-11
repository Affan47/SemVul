checkforreplay ( void )
{
   if ( !actmap->replayinfo )
      return;

   int rpnum  = 0;
   int s = actmap->actplayer + 1;
   if ( s >= 8 )
       s = 0;
   while ( s != actmap->actplayer ) {
       if ( actmap->replayinfo->map[s] && actmap->replayinfo->guidata[s] )
          rpnum++;

       if ( s < 7 )
          s++;
       else
          s = 0;
   }


   if ( actmap->replayinfo  &&  rpnum  &&  (actmap->player[ actmap->actplayer ].stat == Player::human || actmap->player[ actmap->actplayer ].stat == Player::supervisor) )
      if (choice_dlg("run replay of last turn ?","~y~es","~n~o") == 1) {

         MainScreenWidget::StandardActionLocker locker( mainScreenWidget, MainScreenWidget::LockOptions::Menu );
         ReplayGuiIconHandleHandler guiIconHandler;

         int s = actmap->actplayer + 1;
         if ( s >= 8 )
            s = 0;
         while ( s != actmap->actplayer ) {
            if ( s >= 8 )
               s = 0;

             runSpecificReplay(s, actmap->actplayer );

             if ( s < 7 )
                 s++;
              else
                 s = 0;
          }


      }
}
