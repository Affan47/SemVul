getAuxData(le_uint32 auxData[], LEErrorCode &success) const
{
    if (LE_FAILURE(success)) {
      return;
    }

    if (auxData == NULL) {
      success = LE_ILLEGAL_ARGUMENT_ERROR;
      return;
    }

    if (fAuxData == NULL) {
      success = LE_NO_LAYOUT_ERROR;
      return;
    }

    LE_ARRAY_COPY(auxData, fAuxData, fGlyphCount);
}
