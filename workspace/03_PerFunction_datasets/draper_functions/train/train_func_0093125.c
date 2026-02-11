cloneInstance(UObject* instance) const {
        UnicodeString *s = dynamic_cast<UnicodeString *>(instance);
        if(s != NULL) {
            return s->clone();
        } else {
#ifdef U_DEBUG_CALSVC_F
            UErrorCode status2 = U_ZERO_ERROR;
            fprintf(stderr, "Cloning a %s calendar with tz=%ld\n", ((Calendar*)instance)->getType(), ((Calendar*)instance)->get(UCAL_ZONE_OFFSET, status2));
#endif
            return ((Calendar*)instance)->clone();
        }
    }
