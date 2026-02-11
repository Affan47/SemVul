detectAll(int32_t &maxMatchesFound, UErrorCode &status)
{
    if(!textIn->isSet()) {
        status = U_MISSING_RESOURCE_ERROR;

        return NULL;
    } else if(fFreshTextSet) {
        CharsetRecognizer *csr;
        int32_t            detectResults;
        int32_t            confidence;
        int32_t            i;

        textIn->MungeInput(fStripTags);


        resultCount = 0;
        for (i = 0; i < fCSRecognizers_size; i += 1) {
            csr = fCSRecognizers[i];
            detectResults = csr->match(textIn);
            confidence = detectResults;

            if (confidence > 0)  {
                resultArray[resultCount++]->set(textIn, csr, confidence);
            }
        }

        for(i = resultCount; i < fCSRecognizers_size; i += 1) {
            resultArray[i]->set(textIn, 0, 0);
        }

        uprv_sortArray(resultArray, resultCount, sizeof resultArray[0], charsetMatchComparator, NULL, TRUE, &status);


        int32_t j, k;
        for (i=0; i<resultCount; i++) {
            const char *charSetName = resultArray[i]->getName();
            for (j=i+1; j<resultCount; ) {
                if (uprv_strcmp(charSetName, resultArray[j]->getName()) != 0) {

                    j++;
                } else {

                    CharsetMatch *duplicate = resultArray[j];
                    for (k=j; k<resultCount-1; k++) {
                        resultArray[k] = resultArray[k+1];
                    }
                    resultCount--;
                    resultArray[resultCount] = duplicate;
                }
            }
        }

        fFreshTextSet = FALSE;
    }

    maxMatchesFound = resultCount;

    return resultArray;
}
