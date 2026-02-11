getPrevNormalizedChar(collIterate *data, UErrorCode *status)
{
    UChar  prevch;
    UChar  ch;
    UChar *start;
    UBool  innormbuf = (UBool)(data->flags & UCOL_ITER_INNORMBUF);
    UChar *pNull = NULL;
    if ((data->flags & (UCOL_ITER_NORM | UCOL_ITER_INNORMBUF)) == 0 ||
        (innormbuf && *(data->pos - 1) != 0)) {


      if(data->flags & UCOL_USE_ITERATOR) {
        data->iterator->move(data->iterator, -1, UITER_CURRENT);
        return (UChar)data->iterator->next(data->iterator);
      } else {
        return *(data->pos - 1);
      }
    }

    start = data->pos;
    if ((data->fcdPosition==NULL)||(data->flags & UCOL_ITER_HASLEN)) {

        if ((start - 1) == data->string) {
            return *(start - 1);
        }
        start --;
        ch     = *start;
        prevch = *(start - 1);
    }
    else {


        if (data->fcdPosition == data->string) {

            insertBufferFront(data, data->pos - 1, *(data->fcdPosition));
            data->fcdPosition = NULL;
            return *(data->pos - 1);
        }
        pNull  = data->pos - 1;
        start  = data->fcdPosition;
        ch     = *start;
        prevch = *(start - 1);
    }


    if (data->fcdPosition > start &&
       (ch >= NFC_ZERO_CC_BLOCK_LIMIT_ || prevch >= NFC_ZERO_CC_BLOCK_LIMIT_))
    {


        UChar *backuppos = data->pos;
        data->pos = start;
        if (collPrevIterFCD(data)) {
            normalizePrevContraction(data, status);
            return *(data->pos - 1);
        }
        data->pos = backuppos;
        data->fcdPosition ++;
    }

    if (innormbuf) {


        insertBufferFront(data, pNull, ch);
        data->fcdPosition --;
    }

    return ch;
}
