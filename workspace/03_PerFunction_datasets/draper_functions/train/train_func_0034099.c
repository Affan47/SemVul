check_ram(void)
{
        int s;

        p1 = *p;


        *p = ~p1;
        p2 = *p;
        s = 0;


        if ((0xff & p1) != (0xff & p2)) {
                s++;
        }
        if ((0xff00 & p1) != (0xff00 & p2)) {
                s++;
        }
        if ((0xff0000 & p1) != (0xff0000 & p2)) {
                s++;
        }
        if ((0xff000000 & p1) != (0xff000000 & p2)) {
                s++;
        }
        if (s == 4) {

                return 1;
        }

        return 0;
}
