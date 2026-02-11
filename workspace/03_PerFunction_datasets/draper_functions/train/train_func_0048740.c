iswall_or_stone(int x, int y)
{
    int type;


    if (!isok(x,y)) return true;

    type = levl[x][y].typ;
    return (type == STONE || IS_WALL(type) || IS_DOOR(type) ||
            type == SDOOR || type == IRONBARS);
}
