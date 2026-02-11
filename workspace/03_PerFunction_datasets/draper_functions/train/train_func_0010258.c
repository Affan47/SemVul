checkIDSuffix(const char *itemName, const char *id, int32_t idLength, const char *suffix,
              CheckDependency check, void *context,
              UErrorCode *pErrorCode) {
    char target[200];
    makeTargetName(itemName, id, idLength, suffix, target, (int32_t)sizeof(target), pErrorCode);
    if(U_SUCCESS(*pErrorCode)) {
        check(context, itemName, target);
    }
}
