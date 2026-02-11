convertPhaseCData(u_char* buf, u_long& totdata, u_int fillorder,
			    const Class2Params& params, const Class2Params& newparams, uint32& rows)
{
    MemoryDecoder dec(buf, params.pageWidth(), totdata, fillorder, params.is2D(), (params.df == DF_2DMMR));
    u_char* data = dec.convertDataFormat(newparams);
    totdata = dec.getCC();
    rows = dec.getRows();
    return (data);
}
