handle_input (int    input,
                         FILE   *output)
{
    static char         readbuf[1024+1];
    int                 i;
    int                 bytes_read;


    do
    {
        bytes_read = com_read (input, readbuf, sizeof (readbuf) - 1);


        for (i = 0; i < bytes_read; i++)
        {
            if (esc_seq)
            {
                esc_seq = 0;
            }
            else
            {
                switch (readbuf[i])
                {
                    case '\r':
                        break;
                    case 27:
                        esc_seq++;
                        break;
                    default:
                        putc (readbuf[i], output);
                }
            }
        }
    } while (bytes_read > 0);
    fflush (output);

    return (bytes_read);
}
