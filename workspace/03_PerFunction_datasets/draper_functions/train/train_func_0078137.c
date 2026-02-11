d1mach_(integer *i)
{


    static integer sc = 987;
    static struct {
	integer e_1[10];
	doublereal e_2;
    } equiv_4 = { { 0, 1048576, -1, 2146435071, 0, 1017118720, 0,
		    1018167296, 1352628735, 1070810131 }, 0.0 };


    doublereal ret_val = 0.0;


     int s_stop();
    integer s_wsfe(), do_fio(), e_wsfe();


#define log10 ((integer *)&equiv_4 + 8)
#define dmach ((doublereal *)&equiv_4)
#define large ((integer *)&equiv_4 + 2)
#define small ((integer *)&equiv_4)
#define diver ((integer *)&equiv_4 + 6)
#define right ((integer *)&equiv_4 + 4)


    if (sc != 987) {
exit(0);
    }

    if (dmach[3] >= 1.) {
 exit(0);
    }
    if (*i < 1 || *i > 5) {
	goto L999;
    }
    ret_val = dmach[*i - 1];
    return ret_val;
L999:


    return ret_val;
}
