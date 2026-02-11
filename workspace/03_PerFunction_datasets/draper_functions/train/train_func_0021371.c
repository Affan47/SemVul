parseConverterOptions(const char *inName,
                      UConverterNamePieces *pPieces,
                      UConverterLoadArgs *pArgs,
                      UErrorCode *err)
{
    char *cnvName = pPieces->cnvName;
    char c;
    int32_t len = 0;

    pArgs->name=inName;
    pArgs->locale=pPieces->locale;
    pArgs->options=pPieces->options;


    while((c=*inName)!=0 && c!=UCNV_OPTION_SEP_CHAR) {
        if (++len>=UCNV_MAX_CONVERTER_NAME_LENGTH) {
            *err = U_ILLEGAL_ARGUMENT_ERROR;
            pPieces->cnvName[0]=0;
            return;
        }
        *cnvName++=c;
        inName++;
    }
    *cnvName=0;
    pArgs->name=pPieces->cnvName;


    while((c=*inName)!=0) {
        if(c==UCNV_OPTION_SEP_CHAR) {
            ++inName;
        }


        if(uprv_strncmp(inName, "locale=", 7)==0) {

            char *dest=pPieces->locale;


            inName+=7;
            len=0;
            while((c=*inName)!=0 && c!=UCNV_OPTION_SEP_CHAR) {
                ++inName;

                if(++len>=ULOC_FULLNAME_CAPACITY) {
                    *err=U_ILLEGAL_ARGUMENT_ERROR;
                    pPieces->locale[0]=0;
                    return;
                }

                *dest++=c;
            }
            *dest=0;
        } else if(uprv_strncmp(inName, "version=", 8)==0) {

            inName+=8;
            c=*inName;
            if(c==0) {
                pArgs->options=(pPieces->options&=~UCNV_OPTION_VERSION);
                return;
            } else if((uint8_t)(c-'0')<10) {
                pArgs->options=pPieces->options=(pPieces->options&~UCNV_OPTION_VERSION)|(uint32_t)(c-'0');
                ++inName;
            }
        } else if(uprv_strncmp(inName, "swaplfnl", 8)==0) {
            inName+=8;
            pArgs->options=(pPieces->options|=UCNV_OPTION_SWAP_LFNL);

        } else {

            while(((c = *inName++) != 0) && (c != UCNV_OPTION_SEP_CHAR)) {
            }
            if(c==0) {
                return;
            }
        }
    }
}
