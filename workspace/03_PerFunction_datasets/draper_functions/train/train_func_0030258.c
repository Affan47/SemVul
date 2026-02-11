skipBOM(int cThis)
{

    if (cThis == 0xEF) {
    	cThis = getRawTexChar();
    	if (cThis == 0xBB) {
     		cThis = getRawTexChar();
    		if (cThis == 0xBF) {
    			CmdFontEncoding(ENCODING_UTF8);
     			cThis = getRawTexChar();
     			diagnostics(2, "UTF 8 BOM encountered, now assuming UTF8 input");
     		}
    	}
    }


    if (cThis == 0xFE) {
    	cThis = getRawTexChar();
    	if (cThis == 0xFF)
     		diagnostics(2, "UTF 16 is not supported, you might try converting to UTF8");
    }

    return cThis;
}
