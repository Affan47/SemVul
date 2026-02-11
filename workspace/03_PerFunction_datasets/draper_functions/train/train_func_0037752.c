fill (const BmpPixel &pixel)
{
    BmpPixmap *temp = new BmpPixmap (*this);
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            *temp->pdata [i][j] = pixel;
        }
    }
    return *temp;
}
