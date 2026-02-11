av_opt_set_defaults2(void *s, int mask, int flags)
{
    const AVOption *opt = NULL;
    while ((opt = av_next_option(s, opt)) != NULL) {
        if((opt->flags & mask) != flags)
            continue;
        switch(opt->type) {
            case FF_OPT_TYPE_CONST:

            break;
            case FF_OPT_TYPE_FLAGS:
            case FF_OPT_TYPE_INT: {
                int val;
                val = opt->default_val;
                av_set_int(s, opt->name, val);
            }
            break;
            case FF_OPT_TYPE_INT64:
                if((double)(opt->default_val+0.6) == opt->default_val)
                    av_log(s, AV_LOG_DEBUG, "loss of precission in default of %s\n", opt->name);
                av_set_int(s, opt->name, opt->default_val);
            break;
            case FF_OPT_TYPE_FLOAT: {
                double val;
                val = opt->default_val;
                av_set_double(s, opt->name, val);
            }
            break;
            case FF_OPT_TYPE_RATIONAL: {
                AVRational val;
                val = av_d2q(opt->default_val, INT_MAX);
                av_set_q(s, opt->name, val);
            }
            break;
            case FF_OPT_TYPE_STRING:
            case FF_OPT_TYPE_BINARY:

            break;
            default:
                av_log(s, AV_LOG_DEBUG, "AVOption type %d of option %s not implemented yet\n", opt->type, opt->name);
        }
    }
}
