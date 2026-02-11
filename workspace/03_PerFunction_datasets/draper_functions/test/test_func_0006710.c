nvparse(const char * input_string, int argc ,...)
{
    if (NULL == input_string)
    {
        errors.set("NULL string passed to nvparse");
        return;
    }

    char * instring = strdup(input_string);


    if(is_rc10(instring))
    {
        if(rc10_init(instring))
        {
            rc10_parse();
        }
    }


    else if(is_ts10(instring))
    {
        if(ts10_init(instring))
        {
            ts10_parse();
        }
    }


    else if(is_avp10(instring))
    {
        if(avp10_init(instring))
        {
            avp10_parse();
        }
    }

#if !defined(__APPLE__)

    else if(is_vcp10(instring))
    {
        if(vcp10_init(instring))
        {
            vcp10_parse();
        }
    }


    else if(is_vsp10(instring))
    {
        if(vsp10_init(instring))
        {
            vsp10_parse(argc);
        }
    }


    else if(is_vp10(instring))
    {
        if(vp10_init(instring))
        {
            vp10_parse();
        }
    }


    else if ( is_vs10(instring) )
    {
        if(vs10_init(instring))
        {
            vs10_parse();
            vs10_load_program();
        }

    }
    else if (is_ps10(instring))
    {
        if(ps10_init(instring))
        {
            va_list ap;
            std::vector<int> argv;
            va_start(ap,argc);
            for (int i=0;i<argc;++i)
            {
                int arg = va_arg(ap,int);
                argv.push_back(arg);
            }
            va_end(ap);
            if (!ps10_set_map(argv))
                return;
            ps10_parse();
        }
    }
#endif
    else
    {
        errors.set("invalid string.\n "
                   "first characters must be: !!ARBvp1.0 or !!VP1.0 or !!VSP1.0 or !!RC1.0 or !!TS1.0\n "
                   "or it must be a valid DirectX 8.0 Vertex Shader");
    }
    free(instring);
}
