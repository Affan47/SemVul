load_perl_callback(Loader_state_base *cb_data, const nytp_tax_index tag, ...)
{
    Loader_state_callback *state = (Loader_state_callback *)cb_data;
    dTHXa(state->interp);
    dSP;
    va_list args;
    SV **cb_args = state->cb_args;
    int i = 0;
    char type;
    const char *arglist = callback_info[tag].args;
    const char *const description = callback_info[tag].description;

    if (!arglist) {
        if (description)
            croak("Type '%s' passed to perl callback incorrectly", description);
        else
            croak("Unknown type %d passed to perl callback", tag);
    }

    if (!state->cb[tag])
        return;

    if (trace_level >= 9) {
        logwarn("\tcallback %s[%s] \n", description, arglist);
    }

    sv_setuv_mg(state->input_chunk_seqn_sv, state->base_state.input_chunk_seqn);

    va_start(args, tag);

    PUSHMARK(SP);

    XPUSHs(state->tag_names[tag]);

    while ((type = *arglist++)) {
        switch(type) {
        case 'u':
        {
            unsigned int u = va_arg(args, unsigned int);

            sv_setuv(cb_args[i], u);
            XPUSHs(cb_args[i++]);
            break;
        }
        case 'i':
        {
            I32 i32 = va_arg(args, I32);

            sv_setuv(cb_args[i], i32);
            XPUSHs(cb_args[i++]);
            break;
        }
        case 'n':
        {
            NV n = va_arg(args, NV);

            sv_setnv(cb_args[i], n);
            XPUSHs(cb_args[i++]);
            break;
        }
        case 's':
        {
            SV *sv = va_arg(args, SV *);

            sv_setsv(cb_args[i], sv);
            XPUSHs(cb_args[i++]);
            break;
        }
        case 'S':
        {
            SV *sv = va_arg(args, SV *);

            XPUSHs(sv_2mortal(sv));
            break;
        }
        case '3':
        {
            char *p = va_arg(args, char *);
            unsigned long len = va_arg(args, unsigned long);
            unsigned int utf8 = va_arg(args, unsigned int);

            sv_setpvn(cb_args[i], p, len);
            if (utf8)
                SvUTF8_on(cb_args[i]);
            else
                SvUTF8_off(cb_args[i]);

            XPUSHs(cb_args[i++]);
            break;
        }

        default:
            croak("Bad type '%c' in perl callback", type);
        }
    }
    va_end(args);
    assert(i <= C_ARRAY_LENGTH(state->cb_args));

    PUTBACK;
    call_sv((SV *)state->cb[tag], G_DISCARD);
}
