make_wall_free_list(int xsize, int ysize, free_walls_struct *free_walls) {
    int i, j, count;

    count = 0;

    if (free_walls->wall_free_size < 0)
        return;
    free_walls->wall_x_list = (int *)calloc(sizeof(int), free_walls->wall_free_size);
    free_walls->wall_y_list = (int *)calloc(sizeof(int), free_walls->wall_free_size);


    for (i = 2; i < xsize-2; i++) {
        free_walls->wall_x_list[count] = i;
        free_walls->wall_y_list[count] = 0;
        count++;
        free_walls->wall_x_list[count] = i;
        free_walls->wall_y_list[count] = ysize-1;
        count++;
    }


    for (j = 2; j < ysize-2; j++) {
        free_walls->wall_x_list[count] = 0;
        free_walls->wall_y_list[count] = j;
        count++;
        free_walls->wall_x_list[count] = xsize-1;
        free_walls->wall_y_list[count] = j;
        count++;
    }
}
