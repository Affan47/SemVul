createFollowerContext( GameMap* gamemap )
{
   ReplayContext context;


   context.gamemap = gamemap;
   context.actingPlayer = &gamemap->getPlayer( gamemap->actplayer );
   context.parentAction = NULL;
   context.viewingPlayer = gamemap->getPlayerView();
   context.actionContainer = &gamemap->actions;
   return context;
}
