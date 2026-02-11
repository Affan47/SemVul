ninety_scenario(uint32_t n, uint32_t *data)
{
    srand(time(NULL));
    for(uint32_t i = 0; i < n; i++) {
        if(rand() % 100 >= 90)
            data[i] = rand() % n;
        else
            data[i] = i;
    }
}
