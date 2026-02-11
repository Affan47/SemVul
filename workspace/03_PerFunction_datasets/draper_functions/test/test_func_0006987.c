do_black_correction(float kvalue, int kcorrect[256])
{
        int i;

        for (i = 0; i < 256; i++) {
                kcorrect[i] = (int)(100.0 * kvalue * (pow(10.0, pow((i / 255.0), 3.0)) - 1.0));
        }

        return;
}
