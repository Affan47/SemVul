utext_strFromUTF8(UChar *dest,
              int32_t destCapacity,
              int32_t *pDestLength,
              const char* src,
              int32_t srcLength,
              UErrorCode *pErrorCode
              )
{

    UChar *pDest = dest;
    UChar *pDestLimit = (dest!=NULL)?(dest+destCapacity):NULL;
    UChar32 ch=0;
    int32_t index = 0;
    int32_t reqLength = 0;
    uint8_t* pSrc = (uint8_t*) src;


    while((index < srcLength)&&(pDest<pDestLimit)){
        ch = pSrc[index++];
        if(ch <=0x7f){
            *pDest++=(UChar)ch;
        }else{
            ch=utf8_nextCharSafeBody(pSrc, &index, srcLength, ch, -1);
            if(ch<0){
                ch = 0xfffd;
            }
            if(U_IS_BMP(ch)){
                *(pDest++)=(UChar)ch;
            }else{
                *(pDest++)=U16_LEAD(ch);
                if(pDest<pDestLimit){
                    *(pDest++)=U16_TRAIL(ch);
                }else{
                    reqLength++;
                    break;
                }
            }
        }
    }

    while(index < srcLength){
        ch = pSrc[index++];
        if(ch <= 0x7f){
            reqLength++;
        }else{
            ch=utf8_nextCharSafeBody(pSrc, &index, srcLength, ch, -1);
            if(ch<0){
                ch = 0xfffd;
            }
            reqLength+=U16_LENGTH(ch);
        }
    }

    reqLength+=(int32_t)(pDest - dest);

    if(pDestLength){
        *pDestLength = reqLength;
    }


    u_terminateUChars(dest,destCapacity,reqLength,pErrorCode);

    return dest;
}
