expandName(UCharNames *names,
           const uint8_t *name, uint16_t nameLength, UCharNameChoice nameChoice,
           char *buffer, uint16_t bufferLength) {
    uint16_t *tokens=(uint16_t *)names+8;
    uint16_t token, tokenCount=*tokens++, bufferPos=0;
    uint8_t *tokenStrings=(uint8_t *)names+names->tokenStringOffset;
    uint8_t c;

    if(nameChoice==U_UNICODE_10_CHAR_NAME || nameChoice==U_ISO_COMMENT) {


        if((uint8_t)';'>=tokenCount || tokens[(uint8_t)';']==(uint16_t)(-1)) {
            while(nameLength>0) {
                --nameLength;
                if(*name++==';') {
                    break;
                }
            }
            if(nameChoice==U_ISO_COMMENT) {

                while(nameLength>0) {
                    --nameLength;
                    if(*name++==';') {
                        break;
                    }
                }
            }
        } else {


            nameLength=0;
        }
    }


    while(nameLength>0) {
        --nameLength;
        c=*name++;

        if(c>=tokenCount) {
            if(c!=';') {

                WRITE_CHAR(buffer, bufferLength, bufferPos, c);
            } else {

                break;
            }
        } else {
            token=tokens[c];
            if(token==(uint16_t)(-2)) {

                token=tokens[c<<8|*name++];
                --nameLength;
            }
            if(token==(uint16_t)(-1)) {
                if(c!=';') {

                    WRITE_CHAR(buffer, bufferLength, bufferPos, c);
                } else {


                    if(!bufferPos && nameChoice == U_EXTENDED_CHAR_NAME) {
                        if ((uint8_t)';'>=tokenCount || tokens[(uint8_t)';']==(uint16_t)(-1)) {
                            continue;
                        }
                    }

                    break;
                }
            } else {

                uint8_t *tokenString=tokenStrings+token;
                while((c=*tokenString++)!=0) {
                    WRITE_CHAR(buffer, bufferLength, bufferPos, c);
                }
            }
        }
    }


    if(bufferLength>0) {
        *buffer=0;
    }

    return bufferPos;
}
