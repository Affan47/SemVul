ajSeqBamHeaderSetTextC(AjPSeqBamHeader header, const char* txt)
{

    if(header->text)
	AJFREE(header->text);

    header->l_text = strlen(txt);
    header->text = ajCharNewResC(txt, header->l_text + 1);

    return;
}
