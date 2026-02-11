ClassifyPosition(const TanBoard anBoard, const bgvariation bgv)
{
    int nOppBack = -1, nBack = -1;

    for (nOppBack = 24; nOppBack >= 0; --nOppBack) {
        if (anBoard[0][nOppBack]) {
            break;
        }
    }

    for (nBack = 24; nBack >= 0; --nBack) {
        if (anBoard[1][nBack]) {
            break;
        }
    }

    if (nBack < 0 || nOppBack < 0)
        return CLASS_OVER;


    switch (bgv) {
    case VARIATION_HYPERGAMMON_1:
        return CLASS_HYPERGAMMON1;

    case VARIATION_HYPERGAMMON_2:
        return CLASS_HYPERGAMMON2;

    case VARIATION_HYPERGAMMON_3:
        return CLASS_HYPERGAMMON3;

    case VARIATION_STANDARD:
    case VARIATION_NACKGAMMON:


        if (nBack + nOppBack > 22) {


            unsigned int const N = 6;
            unsigned int i;
            unsigned int side;

            for (side = 0; side < 2; ++side) {
                unsigned int tot = 0;

                const unsigned int *board = anBoard[side];

                for (i = 0; i < 25; ++i) {
                    tot += board[i];
                }

                if (tot <= N) {
                    return CLASS_CRASHED;
                } else {
                    if (board[0] > 1) {
                        if (tot <= (N + board[0])) {
                            return CLASS_CRASHED;
                        } else {
                            if (board[1] > 1 && (1 + tot - (board[0] + board[1])) <= N) {
                                return CLASS_CRASHED;
                            }
                        }
                    } else {
                        if (tot <= (N + (board[1] - 1))) {
                            return CLASS_CRASHED;
                        }
                    }
                }
            }

            return CLASS_CONTACT;
        } else {

            if (isBearoff(pbc2, anBoard))
                return CLASS_BEAROFF2;

            if (isBearoff(pbcTS, anBoard))
                return CLASS_BEAROFF_TS;

            if (isBearoff(pbc1, anBoard))
                return CLASS_BEAROFF1;

            if (isBearoff(pbcOS, anBoard))
                return CLASS_BEAROFF_OS;

            return CLASS_RACE;

        }

    default:

        g_assert_not_reached();

    }

    return 0;
}
