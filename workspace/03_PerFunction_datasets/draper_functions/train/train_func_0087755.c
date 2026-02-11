_ml_P_FileSys_access (ml_state_t *msp, ml_val_t arg)
{
    ml_val_t	    path = REC_SEL(arg, 0);
    mode_t	    mode = REC_SELWORD(arg, 1);
    int		    sts;

    sts = access (STR_MLtoC(path), mode);

    if (sts == 0)
        return ML_true;
    else
        return ML_false;

}
