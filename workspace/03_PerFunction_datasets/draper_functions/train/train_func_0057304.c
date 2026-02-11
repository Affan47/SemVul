AllocateSectorBuffer(TMPQFile * hf)
{
    TMPQArchive * ha = hf->ha;


    assert(hf->pbFileSector == NULL);
    assert(hf->pFileEntry != NULL);
    assert(hf->dwDataSize != 0);
    assert(hf->ha != NULL);


    hf->dwSectorSize = (hf->pFileEntry->dwFlags & MPQ_FILE_SINGLE_UNIT) ? hf->dwDataSize : ha->dwSectorSize;
    hf->pbFileSector = ALLOCMEM(BYTE, hf->dwSectorSize);
    hf->dwSectorOffs = SFILE_INVALID_POS;


    return (hf->pbFileSector != NULL) ? (int)ERROR_SUCCESS : (int)ERROR_NOT_ENOUGH_MEMORY;
}
