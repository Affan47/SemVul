FloatWidth(float val, float step)
{
    unsigned int precision;
    unsigned int result;


    result = IntWidth((int) val);


    precision = (unsigned int) ceil(-log(step) / log(10));

    if (precision > 0)
    {
        result += precision + 1;
    }

    return result;
}
