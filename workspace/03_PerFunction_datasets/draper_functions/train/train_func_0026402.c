pluck_initialize(sample_type *shiftreg, sample_type *array,
                      long len, double cons)
{
    sample_type suma = 0.0F;
    long k;
    sample_type avea;
    array[1] = 0;
    for (k = len; k > 0; k--, array--) {


        *array = (krand() & 2) - 1;
        suma += *array;
    }
    avea = suma / len;

    for (k = 0; k <= len + 1; k++) shiftreg[k] -= avea;
    shiftreg[len] = 0;
    shiftreg[len + 1] = 0;
}
