unblock_point(x,y)
    int x, y;
{
    dig_point(y,x);


    if (viz_array[y][x]) vision_full_recalc = 1;
}
