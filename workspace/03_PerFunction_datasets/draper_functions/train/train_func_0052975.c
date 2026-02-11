traceBackOne(GridPoint & gridPoint, Grid * grid, int dx, int dy, int dz, GridValue sourceValue, GridValue targetValue) {
    GridPoint next;
    next.baseCost = GridBoardObstacle;

    next.x = gridPoint.x + dx;
    if (next.x < 0 || next.x >= grid->x) {
        return next;
    }

    next.y = gridPoint.y + dy;
    if (next.y < 0 || next.y >= grid->y) {
        return next;
    }

    next.z = gridPoint.z + dz;
    if (next.z < 0 || next.z >= grid->z) {
        return next;
    }

    GridValue nextval = grid->at(next.x, next.y, next.z);
    if (nextval == GridBoardObstacle || nextval == GridPartObstacle || nextval == sourceValue || nextval == 0 || nextval == GridTempObstacle) return next;
    if (nextval == targetValue) {

        next.baseCost = targetValue;
        return next;
    }

    if (targetValue == GridSource) {
        if ((nextval & GridSourceFlag) == 0) return next;
        nextval ^= GridSourceFlag;
    }
    else {
        if (nextval & GridSourceFlag) return next;
    }

    if (nextval < gridPoint.baseCost) {
        next.baseCost = nextval;
    }
    return next;
}
