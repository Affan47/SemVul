reset_Y(unsigned char **block_Y, int width, int height)
{
    int i, j;


    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            block_Y[i][j] = 0;
        }
    }
}
