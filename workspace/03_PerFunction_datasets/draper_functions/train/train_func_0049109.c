sendPage(TIFF* tif, u_int pageChop, bool cover)
{


    if (conf.class2RTFCC) {
	protoTrace("Enable Real-Time Fax Compression Conversion");
	uint16 compression;
	char rtfcc[2];
	rtfcc[0] = DLE;
	TIFFGetField(tif, TIFFTAG_COMPRESSION, &compression);
	if (compression != COMPRESSION_CCITTFAX4) {
	    uint32 g3opts = 0;
	    TIFFGetField(tif, TIFFTAG_GROUP3OPTIONS, &g3opts);
	    if ((g3opts & GROUP3OPT_2DENCODING) == DF_2DMR) {
		rtfcc[1] = 0x6C;
		protoTrace("Reading MR-compressed image file");
	    } else {
		rtfcc[1] = 0x6B;
		protoTrace("Reading MH-compressed image file");
	    }
	} else {
	    rtfcc[1] = 0x6E;
	    protoTrace("Reading MMR-compressed image file");
	}
	putModemData(rtfcc, sizeof (rtfcc));
    }

    protoTrace("SEND begin page");
    if (flowControl == FLOW_XONXOFF)
	setXONXOFF(FLOW_XONXOFF, FLOW_NONE, ACT_FLUSH);
    bool rc = sendPageData(tif, pageChop, cover);
    if (!rc)
	abortDataTransfer();
    else if( conf.class2SendRTC )
	rc = sendRTC(params);
    if (flowControl == FLOW_XONXOFF)
	setXONXOFF(getInputFlow(), FLOW_XONXOFF, ACT_DRAIN);
    protoTrace("SEND end page");
    return (rc);
}
