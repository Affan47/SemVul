init(const Locale *locale, UErrorCode &status) {
    if (U_FAILURE(status)) { return; }
    if (locale == NULL && collator_ == NULL) {
        status = U_ILLEGAL_ARGUMENT_ERROR;
        return;
    }

    initialLabels_         = new UnicodeSet();
    if (initialLabels_ == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return;
    }

    inflowLabel_.setTo((UChar)0x2026);
    overflowLabel_ = inflowLabel_;
    underflowLabel_ = inflowLabel_;

    if (collator_ == NULL) {
        collator_ = static_cast<RuleBasedCollator *>(Collator::createInstance(*locale, status));
        if (U_FAILURE(status)) { return; }
        if (collator_ == NULL) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return;
        }
    }
    collatorPrimaryOnly_ = static_cast<RuleBasedCollator *>(collator_->clone());
    if (collatorPrimaryOnly_ == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return;
    }
    collatorPrimaryOnly_->setAttribute(UCOL_STRENGTH, UCOL_PRIMARY, status);
    firstCharsInScripts_ = firstStringsInScript(status);
    if (U_FAILURE(status)) { return; }
    firstCharsInScripts_->sortWithUComparator(collatorComparator, collatorPrimaryOnly_, status);
    UnicodeString _4E00((UChar)0x4E00);
    UnicodeString _1100((UChar)0x1100);
    UnicodeString _1112((UChar)0x1112);
    if (collatorPrimaryOnly_->compare(_4E00, _1112, status) <= 0 &&
            collatorPrimaryOnly_->compare(_1100, _4E00, status) <= 0) {


        int32_t hanIndex = binarySearch(
                *firstCharsInScripts_, _4E00, *collatorPrimaryOnly_);
        if (hanIndex >= 0) {
            firstCharsInScripts_->removeElementAt(hanIndex);
        }
    }


    for (;;) {
        if (U_FAILURE(status)) { return; }
        if (firstCharsInScripts_->isEmpty()) {

            status = U_ILLEGAL_ARGUMENT_ERROR;
            return;
        }
        if (collatorPrimaryOnly_->compare(
                *static_cast<UnicodeString *>(firstCharsInScripts_->elementAt(0)),
                emptyString_, status) == UCOL_EQUAL) {
            firstCharsInScripts_->removeElementAt(0);
        } else {
            break;
        }
    }

    if (locale != NULL) {
        addIndexExemplars(*locale, status);
    }
}
