OutputLine_asmstub(FILE *fileDest, EXPORT *pexp)
{

    if (pexp->nNameLength == 1 && pexp->pcName[0] == '@')
    {
        fprintf(fileDest, "PUBLIC %sordinal%d\n%sordinal%d: nop\n",
                gpszUnderscore, pexp->nOrdinal, gpszUnderscore, pexp->nOrdinal);
    }
    else if (giArch != ARCH_X86)
    {
        fprintf(fileDest, "PUBLIC _stub_%.*s\n_stub_%.*s: nop\n",
                pexp->nNameLength, pexp->pcName,
                pexp->nNameLength, pexp->pcName);
    }
    else if (pexp->nCallingConvention == CC_STDCALL)
    {
        fprintf(fileDest, "PUBLIC __stub_%.*s@%d\n__stub_%.*s@%d: nop\n",
                pexp->nNameLength, pexp->pcName, pexp->nStackBytes,
                pexp->nNameLength, pexp->pcName, pexp->nStackBytes);
    }
    else if (pexp->nCallingConvention == CC_FASTCALL)
    {
        fprintf(fileDest, "PUBLIC @_stub_%.*s@%d\n@_stub_%.*s@%d: nop\n",
                pexp->nNameLength, pexp->pcName, pexp->nStackBytes,
                pexp->nNameLength, pexp->pcName, pexp->nStackBytes);
    }
    else if (pexp->nCallingConvention == CC_CDECL ||
             pexp->nCallingConvention == CC_STUB)
    {
        fprintf(fileDest, "PUBLIC __stub_%.*s\n__stub_%.*s: nop\n",
                pexp->nNameLength, pexp->pcName,
                pexp->nNameLength, pexp->pcName);
    }
    else if (pexp->nCallingConvention == CC_EXTERN)
    {
        fprintf(fileDest, "PUBLIC __stub_%.*s\n__stub_%.*s:\n",
                pexp->nNameLength, pexp->pcName,
                pexp->nNameLength, pexp->pcName);
    }

    return 1;
}
