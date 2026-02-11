at_cmd_D(at_state_t *s, const char *t)
{
    int ok;
    char *u;
    const char *w;
    char num[100 + 1];
    char ch;


    at_reset_call_info(s);
    s->do_hangup = FALSE;
    s->silent_dial = FALSE;
    t += 1;
    ok = FALSE;


    w = t;
    u = num;
    for (  ;  (ch = *t);  t++)
    {
        if (isdigit(ch))
        {

            *u++ = ch;
        }
        else
        {
            switch (ch)
            {
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case '*':
            case '#':

                if (!s->p.pulse_dial)
                    *u++ = ch;
                break;
            case ' ':
            case '-':


                break;
            case '+':


                break;
            case ',':


                *u++ = ch;
                break;
            case 'T':

                s->p.pulse_dial = FALSE;
                break;
            case 'P':

                s->p.pulse_dial = TRUE;
                break;
            case '!':


                break;
            case 'W':


                break;
            case '@':

                s->silent_dial = TRUE;
                break;
            case 'S':


                break;
            case 'G':
            case 'g':


                break;
            case 'I':
            case 'i':


                break;
            case ';':


                break;
            case '>':


                break;
            default:
                return NULL;
            }
        }
    }
    *u = '\0';
    if ((ok = at_modem_control(s, AT_MODEM_CONTROL_CALL, num)) < 0)
        return NULL;


    return (const char *) -1;
}
