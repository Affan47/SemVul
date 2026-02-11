wstart()
{
    char buf[5];


    sprintf(&buf[2], "ok");
    put_int16(2, &buf[0]);
    if (write_fill(1, buf, 4) != 4) {
        exit(1);
    }
}
