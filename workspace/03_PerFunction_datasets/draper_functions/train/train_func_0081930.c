s2l(char *str, int *arr)
{
    int i = 0;
    int num = 0;
    char *p = str;
    bool in_number = false;
    do {
        if (isdigit(*p)) {
            in_number = true;
            num = num * 10 + *p - '0';
        } else {
            if (in_number) {
                arr[i++] = num;
                num = 0;
            }
            in_number = false;
        }
    } while (*(p++));
    return i;
}
