matrix_copy(matrix* src, matrix* dest)
{
    if((src == NULL) ||
       (dest == NULL) ||
       (src->rows != dest->rows) ||
       (src->columns != dest->columns)) {
        return false;
    }

    for(int i = 0; i < src->rows; i++) {
        for(int j = 0; j < src->columns; j++) {
            dest->data[i][j] = src->data[i][j];
        }
    }
    return true;
}
