_ml_RunT_blast_in (ml_state_t *msp, ml_val_t arg)
{
    bool_t	errFlg = FALSE;
    ml_val_t	obj;

    obj = BlastIn (msp, GET_SEQ_DATAPTR(Byte_t, arg), GET_SEQ_LEN(arg), &errFlg);

    if (errFlg)
	return RAISE_ERROR(msp, "blast_in");
    else
	return obj;

}
