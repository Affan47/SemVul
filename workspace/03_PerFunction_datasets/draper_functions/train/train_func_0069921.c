ScoreMaterial(void)
{
    int score = ScoreWhiteMaterial() - ScoreBlackMaterial();
    return (Pos.GetToMove() == WHITE) ? score : -score;
}
