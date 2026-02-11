run (const int scaledTime)
{
    Situation s = situation (scaledTime);
    if (s == NotTimeYet) {
        return NORMAL;
    }


    if (s == CaughtInBrick) {
        return DEAD;
    }


    if ((gridJ == 1) && (nuggets <= 0) &&
        (grid->heroMoves (gridI, gridJ) & dFlag [STAND])) {
        return WON_LEVEL;
    }


    if (falling && (interval != enemyFallTime)) {
        if (levelPlayer->standOnEnemy (spriteId, gridX, gridY)) {
            interval = enemyFallTime;

        }
    }


    if (levelPlayer->heroCaught (gridX, gridY)) {
        return DEAD;
    }


    if (((s == EndCell) || (pointCtr == (pointsPerCell/2))) &&
        (currDirection != STAND) && (! falling)) {
        int step = ((currAnimation == RUN_R) || (currAnimation == RUN_L)) ?
                    StepSound : ClimbSound;
        if ((s == EndCell) || (step == ClimbSound)) {
            emit soundSignal (step);
        }
    }

    if (s == MidCell) {
        return NORMAL;
    }


    char cellType = nextCell();

    if (cellType == NUGGET) {
        nuggets = levelPlayer->runnerGotGold (spriteId, gridI, gridJ, true);
        emit incScore (250);
        if (nuggets > 0) {
            emit soundSignal (GoldSound);
        }
        else {
            emit soundSignal (LadderSound);
        }
    }

    Direction nextDirection;
    AnimationType nextAnimation;
    bool newFallingState = setNextMovement (HERO, cellType, nextDirection,
                                            nextAnimation, interval);
    if (newFallingState != falling) {
        emit soundSignal (FallSound, newFallingState);
        falling = newFallingState;
    }
    timeLeft += interval;
    dbe2 "%d sprite %02d [%02d,%02d] timeLeft %03d currDir %d nextDir %d "
            "currAnim %d nextAnim %d\n",
      pointCtr, spriteId, gridI, gridJ, timeLeft, currDirection, nextDirection,
      currAnimation, nextAnimation);

    if ((nextDirection == currDirection) && (nextAnimation == currAnimation)) {
        if (nextDirection == STAND) {
            return NORMAL;
        }
    }

    deltaX = movement [nextDirection][X];
    deltaY = movement [nextDirection][Y];


    emit startAnimation (spriteId, true, gridI, gridJ,
                         (interval * pointsPerCell * TickTime) / scaledTime,
                         nextDirection, nextAnimation);
    currAnimation = nextAnimation;
    currDirection = nextDirection;
    return NORMAL;
}
