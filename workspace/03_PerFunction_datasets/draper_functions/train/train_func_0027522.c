processNode(void)
{
    char closeChar;
    int subElementsProcessed = 0;
    char nextChar;
    char* nodeName;
    int nodeNameLength = 0;
    int i;
    int opening = readNextChar();
    if (opening != '<')
    {
        printError("processNode : The first char should be '<' (not '%c')", opening);
        result = PRETTY_PRINTING_INVALID_CHAR_ERROR;
        return;
    }

    putCharInBuffer(opening);


    while (!isWhite(getNextChar()) &&
           getNextChar() != '>' &&
           getNextChar() != '/')
    {
        putNextCharsInBuffer(1);
        ++nodeNameLength;
    }


    nodeName = (char*)malloc(sizeof(char)*nodeNameLength+1);
    if (nodeName == NULL) { PP_ERROR("Allocation error (node name length is %d)", nodeNameLength); return ; }
    nodeName[nodeNameLength] = '\0';
    for (i=0 ; i<nodeNameLength ; ++i)
    {
        int tempIndex = xmlPrettyPrintedIndex-nodeNameLength+i;
        nodeName[i] = xmlPrettyPrinted[tempIndex];
    }

    currentNodeName = nodeName;
    lastNodeOpen = TRUE;


    readWhites(TRUE);
    processElementAttributes();


    subElementsProcessed = 0;
    nextChar = getNextChar();
    if (nextChar == '/')
    {

        if (options->emptyNodeStripping || !options->forceEmptyNodeSplit)
        {
            if (options->emptyNodeStrippingSpace) { putCharInBuffer(' '); }
            putNextCharsInBuffer(2);
        }

        else
        {
            readNextChar();
            readNextChar();

            putCharInBuffer('>');
            if (!options->inlineText)
            {

                putNewLine();
            }

            putCharsInBuffer("</");
            putCharsInBuffer(currentNodeName);
            putCharInBuffer('>');
        }

        lastNodeOpen=FALSE;
        return;
    }
    else if (nextChar == '>')
    {

        putNextCharsInBuffer(1);
        subElementsProcessed = processElements();
    }
    else
    {
        printError("processNode : Invalid character '%c'", nextChar);
        result = PRETTY_PRINTING_INVALID_CHAR_ERROR;
        return;
    }


    closeChar = getNextChar();
    if (closeChar != '<')
    {
        printError("processNode : Invalid character '%c' for closing tag (should be '<')", closeChar);
        result = PRETTY_PRINTING_INVALID_CHAR_ERROR;
        return;
    }

    do
    {
        closeChar = readNextChar();
        putCharInBuffer(closeChar);
    }
    while(closeChar != '>');


    if (subElementsProcessed == 0)
    {

        if (options->emptyNodeStripping)
        {

            xmlPrettyPrintedIndex -= nodeNameLength+4;
            resetBackwardIndentation(TRUE);

            if (options->emptyNodeStrippingSpace) { putCharInBuffer(' '); }
            putCharsInBuffer("/>");
        }

        else if (options->inlineText)
        {

            xmlPrettyPrintedIndex -= nodeNameLength+3;
            resetBackwardIndentation(TRUE);


            putCharsInBuffer("</");
            putCharsInBuffer(currentNodeName);
            putCharInBuffer('>');
        }
    }


    lastNodeOpen = FALSE;


    free(nodeName);
    nodeName = NULL;
    currentNodeName = NULL;
}
