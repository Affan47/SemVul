MakeNullMove (int side)


{
   GameRec *g;

   GameCnt++;
   g = &Game[GameCnt];
   g->epsq = board.ep;
   g->bflag = board.flag;
   g->hashkey = HashKey;
   if (board.ep > -1)
      HashKey ^= ephash[board.ep];
   HashKey ^= Sidehash;
   board.ep = -1;
   board.side = 1^side;


   g->move = NULLMOVE;
   return;
}
