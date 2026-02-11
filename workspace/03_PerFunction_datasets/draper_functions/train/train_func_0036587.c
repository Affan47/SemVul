setDirectionByKey (const Direction dirn,
                                        const bool pressed)

{


    if (playback || (playState == NotReady) || (controlMode == MOUSE)) {
        return;
    }

    if ((dirn == DIG_LEFT) || (dirn == DIG_RIGHT)) {

        if (playState == Ready) {
            playState = Playing;
            T = 0;
        }
        if (controlMode == KEYBOARD) {

            newDirection = STAND;
        }
        startDigging (dirn);
        record (1, (uchar) (DIRECTION_CODE + dirn));
    }
    else if (controlMode == KEYBOARD) {
        if (playState == Ready) {
            playState = Playing;
            T = 0;
        }

        if ((holdKeyOption == CLICK_KEY) && pressed && (dirn != direction)) {
            newDirection = dirn;
        }
        else if (holdKeyOption == HOLD_KEY) {
            int sign = pressed ? +1 : -1;
            dX = dX + sign * movement [dirn][X];
            dY = dY + sign * movement [dirn][Y];
        }
    }
}
