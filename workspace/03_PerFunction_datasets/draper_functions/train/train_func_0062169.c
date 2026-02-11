countReachable(const std::vector<bool> &boardIn, position player_pos,
        std::map<position, int> &corridorEntrances)
{
    std::vector<bool> board(boardIn);

    board[index(player_pos)] = false;

    fillUnreachableSquares(board, player_pos);

    pruneCorridors(board, player_pos, corridorEntrances);

    int corridorDepth = 0;
    int checkerDiff = 0;
    int corridorSign = 0;

    int fill = floodFillCorr(board, player_pos, corridorDepth, checkerDiff,
            corridorSign, corridorEntrances);

    int checkerSub = 0;
    int playerSign = checkerSign(player_pos);
    if (corridorSign == 0) {
        if (checkerDiff == 0)
            checkerSub = 0;
        else if (playerSign * checkerDiff > 0)
            checkerSub = abs(checkerDiff);
        else
            checkerSub = abs(checkerDiff) - 1;
    } else {
        if (playerSign * corridorSign < 0)
            checkerSub = abs(checkerDiff);
        else if (playerSign * checkerDiff > 0)
            checkerSub = abs(checkerDiff) - 1;
        else
            checkerSub = abs(checkerDiff) + 1;
    }


    return fill + corridorDepth - checkerSub;
}
