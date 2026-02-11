xtoi (
    CHAR16  *str
    )

{
    UINTN       u;
    CHAR16      c;


    while (*str && *str == ' ') {
        str += 1;
    }


    u = 0;
    while ((c = *(str++))) {
        if (c >= 'a'  &&  c <= 'f') {
            c -= 'a' - 'A';
        }

        if ((c >= '0'  &&  c <= '9')  ||  (c >= 'A'  &&  c <= 'F')) {
            u = (u << 4)  |  (c - (c >= 'A' ? 'A'-10 : '0'));
        } else {
            break;
        }
    }

    return u;
}
