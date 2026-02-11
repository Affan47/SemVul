update_dataset(dataset *data, work_results *wr)
{
    uint64_t i, j;
    for (i = 0; i < KEYSTREAM_LENGTH; i++)
        for (j = 0; j < 256; j++)
            data->epmf[i][j] += wr->epmf[i][j];
}
