initLabels(UVector &indexCharacters, UErrorCode &errorCode) const {
    const Normalizer2 *nfkdNormalizer = Normalizer2::getNFKDInstance(errorCode);
    if (U_FAILURE(errorCode)) { return; }

    const UnicodeString &firstScriptBoundary = *getString(*firstCharsInScripts_, 0);
    const UnicodeString &overflowBoundary =
        *getString(*firstCharsInScripts_, firstCharsInScripts_->size() - 1);


    UnicodeSetIterator iter(*initialLabels_);
    while (iter.next()) {
        const UnicodeString *item = &iter.getString();
        LocalPointer<UnicodeString> ownedItem;
        UBool checkDistinct;
        int32_t itemLength = item->length();
        if (!item->hasMoreChar32Than(0, itemLength, 1)) {
            checkDistinct = FALSE;
        } else if(item->charAt(itemLength - 1) == 0x2a &&
                item->charAt(itemLength - 2) != 0x2a) {


            ownedItem.adoptInstead(new UnicodeString(*item, 0, itemLength - 1));
            item = ownedItem.getAlias();
            if (item == NULL) {
                errorCode = U_MEMORY_ALLOCATION_ERROR;
                return;
            }
            checkDistinct = FALSE;
        } else {
            checkDistinct = TRUE;
        }
        if (collatorPrimaryOnly_->compare(*item, firstScriptBoundary, errorCode) < 0) {

        } else if (collatorPrimaryOnly_->compare(*item, overflowBoundary, errorCode) >= 0) {

        } else if (checkDistinct &&
                collatorPrimaryOnly_->compare(*item, separated(*item), errorCode) == 0) {


        } else {
            int32_t insertionPoint = binarySearch(indexCharacters, *item, *collatorPrimaryOnly_);
            if (insertionPoint < 0) {
                indexCharacters.insertElementAt(
                    ownedString(*item, ownedItem, errorCode), ~insertionPoint, errorCode);
            } else {
                const UnicodeString &itemAlreadyIn = *getString(indexCharacters, insertionPoint);
                if (isOneLabelBetterThanOther(*nfkdNormalizer, *item, itemAlreadyIn)) {
                    indexCharacters.setElementAt(
                        ownedString(*item, ownedItem, errorCode), insertionPoint);
                }
            }
        }
    }
    if (U_FAILURE(errorCode)) { return; }


    int32_t size = indexCharacters.size() - 1;
    if (size > maxLabelCount_) {
        int32_t count = 0;
        int32_t old = -1;
        for (int32_t i = 0; i < indexCharacters.size();) {
            ++count;
            int32_t bump = count * maxLabelCount_ / size;
            if (bump == old) {
                indexCharacters.removeElementAt(i);
            } else {
                old = bump;
                ++i;
            }
        }
    }
}
