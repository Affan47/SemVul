xmlinReadXml(AjPXmlin xmlin, AjPXml xml)
{
    AjPFilebuff buff;

    ajDebug("xmlinReadXml\n");
    ajXmlClear(xml);
    buff = xmlin->Input->Filebuff;


    xml->Doc = ajDomImplementationCreateDocument(NULL,NULL,NULL);

    if (ajDomReadFilebuffText(xml->Doc,buff,
                              xmlin->Input->Text, &xml->TextPtr) == -1)
    {
	ajDomDocumentDestroyNode(xml->Doc, &xml->Doc);
        xml->Doc = NULL;
	return AJFALSE;
    }

    ajFilebuffClear(buff, 0);

    return ajTrue;
}
