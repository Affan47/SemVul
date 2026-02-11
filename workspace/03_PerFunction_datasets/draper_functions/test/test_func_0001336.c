CmdAcrodef(int code)
{
    char *acDef = NULL, *acShort = NULL, *acLong = NULL;
    acroEntry *thisEntry = NULL;

    acDef   = getBraceParam();
    acShort = getBracketParam();
    acLong  = getBraceParam();


    switch (code) {
    case ACRONYM_NEWACRO:
        thisEntry = createEntry(acDef);

        if (acShort == NULL)
            acShort = acDef;

        if (NULL != thisEntry) {
            thisEntry->acShort    = acShort;
            thisEntry->acLong     = acLong;

            acroDiag(thisEntry);
        } else {
            diagnostics(ERROR,"Out of memory!");
        }
        break;
    case ACRONYM_NEWACROPLURAL:
        thisEntry = createEntry(acDef);

        if (NULL != thisEntry) {
            thisEntry->acShortPlural = (acShort == NULL) ? regularPlural(acDef) : acShort;
            thisEntry->acLongPlural  = acLong;
            acroDiag(thisEntry);
        } else {
            diagnostics(ERROR,"Out of memory!");
        }
        break;
    case ACRONYM_ACRO:


        thisEntry = searchEntry(acDef);
        if (NULL != thisEntry) {

            int doPrint;

            doPrint =

                ((thisEntry->used == TRUE) ||
                 (acroPrintOnlyUsed == FALSE));


            if (doPrint) {
                int vspace = getLength("itemsep") + getLength("parsep");
                CmdEndParagraph(0);
                setVspace(vspace);


                startParagraph("acronym", PARAGRAPH_FIRST);
                fprintRTF("{\\b ");
                ConvertString((NULL != acShort) ? acShort : acDef);
                fprintRTF("}\\tab\n");
                ConvertString(acLong);
                if (TRUE == acroPrintWithPage) {
                    char *acroLabel = (char *) malloc(strlen(acDef)+8);
                    if (NULL != acroLabel) {
                        char *acroPage;
                        sprintf(acroLabel,"acro:%s",acDef);
                        acroPage = getLabelPage(acroLabel);
                        if (NULL != acroPage) {
                            fprintRTF(" \\tab ");
                            ConvertString(acroPage);
                        }
                        safe_free(acroPage);
                    }
                    safe_free(acroLabel);
                }
                CmdEndParagraph(0);
            }

        default:
            safe_free(acDef);
            safe_free(acShort);
            safe_free(acLong);
            break;
        }
    }
}
