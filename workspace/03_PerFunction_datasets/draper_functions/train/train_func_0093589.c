setNextMovement (const char spriteType, const char cellType,
                                 Direction & dir,
                                 AnimationType & anim, int & interval)
{
    bool fallingState = false;

    Flags OK = 0;
    if (spriteType == HERO) {
        dir = levelPlayer->getDirection (gridI, gridJ);
        OK  = grid->heroMoves (gridI, gridJ);
    }
    else {
        dir = levelPlayer->getEnemyDirection (gridI, gridJ, leftRightSearch);
        OK  = grid->enemyMoves (gridI, gridJ);
    }
    if ((dir >= nDirections) || (dir < 0)) {
        dir = STAND;
    }

    if (dir == STAND) {
        anim = currAnimation;
    }
    else {
        anim = aType [dir];
    }
    if (((anim == RUN_R) || (anim == RUN_L)) && (cellType == BAR)) {
        anim = (dir == RIGHT) ? CLIMB_R : CLIMB_L;
    }

    interval = runTime;

    KGrEnemy * onEnemy  = levelPlayer->standOnEnemy (spriteId, gridX, gridY);
    bool canStand = (OK & dFlag [STAND]) || (OK == 0) || onEnemy;
    if ((dir == DOWN) && (cellType == BAR)) {
        canStand = false;
    }
    bool cannotMoveAsRequired = (! (OK & dFlag [dir]));


    if ((spriteType == ENEMY) && (cellType == USEDHOLE)) {

        if (currDirection == DOWN) {

            dir = STAND;
            anim = currAnimation;
            interval = trapTime;
            dbe1 "T %05d id %02d Captive at [%02d,%02d]\n",
                 t.elapsed(), spriteId, gridI, gridJ);
        }
        else {

            dir = UP;
            anim = CLIMB_U;
            dbe1 "T %05d id %02d Start climb out at [%02d,%02d]\n",
                 t.elapsed(), spriteId, gridI, gridJ);
        }
    }
    else if ((! canStand) ||
             (onEnemy && (onEnemy->isFalling()) && cannotMoveAsRequired)) {

        fallingState = true;
        interval = onEnemy ? enemyFallTime : fallTime;
        dir  = DOWN;
        anim = (falling) ? currAnimation :
                           ((currDirection == RIGHT) ? FALL_R : FALL_L);
    }
    else if (cannotMoveAsRequired) {

        dir = STAND;
    }

    return fallingState;
}
