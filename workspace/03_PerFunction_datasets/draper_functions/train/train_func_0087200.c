collectScores() {
    gameState.score = current.score;
    if (scores == NULL)
        gameState.scores = NULL;
    else
        gameState.scores = duplicate(scores, header->scoreCount*sizeof(Aword));
}
