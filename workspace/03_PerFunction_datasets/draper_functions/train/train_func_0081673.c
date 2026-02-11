parsefield()
{
    fieldx = 1;
    switch (token[0]) {
    case 'T' :
        dotime();
        break;
    case 'U':
    case 'W':
    case 'H':
    case 'Q':
    case 'S':
    case 'I':
    case '%':
    case '^':
        dur = dodur();
        break;
    case 'R':
        do_a_rest();
        break;
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
        pitch = dopitch();
        pitch_flag = TRUE;
        break;
    case 'P':
        pitch = doabspitch();
        pitch_flag = TRUE;
        break;
    case 'L':
        loud = doloud();
        break;
    case 'N':
        donextdur();
        break;


    case 'K':
        doctrl(PSWITCH_CTRL);
        break;
    case 'M':
        doctrl(MODWHEEL_CTRL);
        break;
    case 'O':
        doctrl(TOUCH_CTRL);
        break;
    case 'X':
        doctrl(VOLUME_CTRL);
        break;
    case 'Y':
        doctrl(BEND_CTRL);
        break;
    case 'Z':
        doprogram();
        break;
    case 'V':
        dovoice();
        break;
    case '~':
        domacro();
        break;
    case '*':
        docomment();
        break;
    case '#':
        doartic();
        break;
    default :
        doerror();
        break;
    }
}
