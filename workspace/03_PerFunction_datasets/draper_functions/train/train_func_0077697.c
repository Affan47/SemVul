move_ahead(void)
{

    if (curr_pntr == buff_pntr) {
        putchar(_BELL);
    }
    else {
        if (buff_flag[curr_pntr] == 2) {
            myputchar(buff[curr_pntr++]);
        }
        myputchar(buff[curr_pntr++]);
    }
    fflush(stdout);
}
