toUnicodeCallback(UConverter *cnv,
                  const uint32_t sourceChar, const uint32_t targetUniChar,
                  UErrorCode* err){
    if(sourceChar>0xff){
        cnv->toUBytes[0] = (uint8_t)(sourceChar>>8);
        cnv->toUBytes[1] = (uint8_t)sourceChar;
        cnv->toULength = 2;
    }
    else{
        cnv->toUBytes[0] =(char) sourceChar;
        cnv->toULength = 1;
    }

    if(targetUniChar == (missingCharMarker-1)){
        *err = U_INVALID_CHAR_FOUND;
    }
    else{
        *err = U_ILLEGAL_CHAR_FOUND;
    }
}
