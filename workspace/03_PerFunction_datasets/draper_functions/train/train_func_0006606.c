D32AddCarry(uint32_t* value, uint32_t i)
{
    uint32_t v = *value;
    uint32_t sum = v + i;
    *value = sum;
    return sum < v || sum < i? 1: 0;
}
