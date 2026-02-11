addParams(fxStr& msg, const Class2Params& params)
{
    msg.append(fxStr::format("<%s, %s, %s, %s, %s>"
	, (params.ln == LN_A4 ? "A4" : params.ln == LN_B4 ? "B4" : "INF")
	, params.verticalResName()
	, params.dataFormatName()
	, params.bitRateName()
	, params.scanlineTimeName()
    ));
}
