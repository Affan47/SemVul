remove_dc_bias(float speech[], int len, float sigout[])
{
    float bias;
    int i;

    bias = 0.0f;
    for (i = 0;  i < len;  i++)
        bias += speech[i];
    bias /= len;
    for (i = 0; i < len;  i++)
        sigout[i] = speech[i] - bias;
}
