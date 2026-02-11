sudokuSolve(L_SUDOKU  *sud)
{
    PROCNAME("sudokuSolve");

    if (!sud)
        return ERROR_INT("sud not defined", procName, 0);

    if (!sudokuValidState(sud->init))
        return ERROR_INT("initial state not valid", procName, 0);

    while (1) {
        if (sudokuNewGuess(sud))
            break;
        if (sud->finished == TRUE)
            break;
    }

    if (sud->failure == TRUE) {
        fprintf(stderr, "Failure after %d guesses\n", sud->nguess);
        return 0;
    }

    fprintf(stderr, "Solved after %d guesses\n", sud->nguess);
    return 1;
}
