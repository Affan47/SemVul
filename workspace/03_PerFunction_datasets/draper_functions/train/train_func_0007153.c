ReadinBlock(TASK *task, HTML_MARKUP *htmlMarkup, STREAM *blockStream) {
    BOOL expand = UnlinkBoolAttributeInMarkup(htmlMarkup, "EXPAND");

    if (htmlMarkup->attrib != NULL) {
        HtpMsg(MSG_WARNING, task->infile,
               "Unhandled %s attribute in %s markup",
               htmlMarkup->attrib->name, htmlMarkup->tag);
    }


    if(CreateBufferWriter(blockStream, htmlMarkup->tag) == FALSE)
    {
        HtpMsg(MSG_ERROR, task->infile,
	       "unable to create stream for %s macro", htmlMarkup->tag);
        return FALSE;
    }

    if (ReadBlockToFile(task, expand, htmlMarkup->tag, blockStream) == FALSE) {
        CloseStream(blockStream);
        FreeMemory(blockStream);
        return FALSE;
    }
    FlushBufferWriter(blockStream);
    return TRUE;
}
