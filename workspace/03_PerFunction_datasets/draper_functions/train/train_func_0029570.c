SaveMemoryBlock(const cmsUInt8Number* Buffer, cmsUInt32Number dwLen, const char* Filename)
{
    FILE* out = fopen(Filename, "wb");
    if (out == NULL) {
        FatalError("Cannot create '%s'", Filename);
        return FALSE;
    }

    if (fwrite(Buffer, 1, dwLen, out) != dwLen) {
        FatalError("Cannot write %ld bytes to %s", dwLen, Filename);
        return FALSE;
    }

    if (fclose(out) != 0) {
        FatalError("Error flushing file '%s'", Filename);
        return FALSE;
    }

    return TRUE;
}
