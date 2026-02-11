active() {


   if (game_status(Game) != PLAYING) return false;


   if (XB->analyse) return true;
   if (!State->computer[White] && !State->computer[Black]) return false;
   if (XB->new_hack || XB->result) return false;

   return true;
}
