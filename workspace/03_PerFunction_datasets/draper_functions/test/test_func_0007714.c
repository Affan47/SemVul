add(le_int32 baseIndex, le_int32 mpreIndex)
{


    if (baseIndex - mpreIndex > 1) {
        fFixupData[fFixupCount].fBaseIndex = baseIndex;
        fFixupData[fFixupCount].fMPreIndex = mpreIndex;

        fFixupCount += 1;
    }
}
