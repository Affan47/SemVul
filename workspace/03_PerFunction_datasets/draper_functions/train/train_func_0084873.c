freeGameState() {

    free(gameState.admin);
    free(gameState.attributes);

    if (gameState.eventQueueTop > 0) {
        free(gameState.eventQueue);
        gameState.eventQueue = NULL;
    }
    if (gameState.scores)
        free(gameState.scores);

    memset(&gameState, 0, sizeof(GameState));
}
