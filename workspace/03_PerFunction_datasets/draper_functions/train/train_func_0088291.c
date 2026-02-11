RetractMove(void)
{
    if(NumGameMoves == 0)
    {
        return;
    }
    PopRepeat();
    NumGameMoves--;
    RootPos.UndoSimpleMove(GameMoves[NumGameMoves]);
    Pos.UndoSimpleMove(GameMoves[NumGameMoves]);
    delete GameMoves[NumGameMoves];
    TranTableSequence--;
}
