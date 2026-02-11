uint64_to_dec(uint64_t num, char dec[40])
{
    int i, l = 0, tr;

    dec[0] = 0;
    while (num > 0 && l < 39) {
        dec[l++] = '0' + num % 10;
        num /= 10;
    }
    dec[l] = 0;


    for (i = 0;i < l / 2; i++) {
        tr = dec[i];
        dec[i] = dec[l - i - 1];
        dec[l - i - 1] = tr;
    }
    return dec;
}
