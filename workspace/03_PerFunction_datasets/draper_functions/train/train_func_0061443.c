canWalkLR (int direction, int x, int y)
{
    if (willNotFall (x, y)) {
        switch (grid->cellType (x+direction, y)) {
        case CONCRETE:
        case BRICK:
        case USEDHOLE:
            return -1;
            break;
        default:


            return +1;
            break;
        }
    }
    else
        return 0;
}
