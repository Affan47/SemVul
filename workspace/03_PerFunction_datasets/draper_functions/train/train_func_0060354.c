ParseSnowieTxt(char *sz,
               int *pnMatchTo, int *pfJacoby, int *UNUSED(p1), int *UNUSED(p2),
               int *pfTurn, char aszPlayer[2][MAX_NAME_LEN], int *pfCrawfordGame,
               int anScore[2], int *pnCube, int *pfCubeOwner, TanBoard anBoard, int anDice[2])
{
    int c;
    char *pc;
    int i, j;

    memset(anBoard, 0, 2 * 25 * sizeof(int));

    c = 0;
    i = 0;
    pc = NextTokenGeneral(&sz, ";");
    while (pc) {

        switch (c) {
        case 0:

            *pnMatchTo = atoi(pc);
            break;
        case 1:

            *pfJacoby = atoi(pc);
            break;
        case 2:
        case 3:

            break;
        case 4:

            *pfTurn = atoi(pc);
            break;
        case 5:
        case 6:

            j = *pfTurn;
            if (c == 6)
                j = !j;

            memset(aszPlayer[j], 0, MAX_NAME_LEN);
            if (*pc)
                strncpy(aszPlayer[j], pc, MAX_NAME_LEN - 1);
            else
                sprintf(aszPlayer[j], "Player %d", j);
            break;
        case 7:

            *pfCrawfordGame = atoi(pc);
            break;
        case 8:

            anScore[*pfTurn] = atoi(pc);
            break;
        case 9:

            anScore[!*pfTurn] = atoi(pc);
            break;
        case 10:

            *pnCube = atoi(pc);
            break;
        case 11:

            j = atoi(pc);
            if (j == 1)
                *pfCubeOwner = *pfTurn;
            else if (j == -1)
                *pfCubeOwner = !*pfTurn;
            else
                *pfCubeOwner = -1;
            break;
        case 12:

            anBoard[1][24] = abs(atoi(pc));
            break;
        case 37:

            anBoard[0][24] = abs(atoi(pc));
            break;
        case 38:
        case 39:

            anDice[c - 38] = atoi(pc);
            break;
        default:

            j = atoi(pc);
            anBoard[j < 0][(j < 0) ? 23 - i : i] = abs(j);
            ++i;

            break;
        }

        pc = NextTokenGeneral(&sz, ";");

        ++c;
        if (c == 40)
            break;

    }

    if (c != 40)
        return -1;

    return 0;
}
