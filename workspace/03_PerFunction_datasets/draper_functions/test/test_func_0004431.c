ajXmlClear(AjPXml xml)
{
    if(MAJSTRGETLEN(xml->Id))
       ajStrSetClear(&xml->Id);

    if(MAJSTRGETLEN(xml->Db))
       ajStrSetClear(&xml->Db);

    if(MAJSTRGETLEN(xml->Setdb))
       ajStrSetClear(&xml->Setdb);

    if(MAJSTRGETLEN(xml->Full))
       ajStrSetClear(&xml->Full);

    if(MAJSTRGETLEN(xml->Qry))
       ajStrSetClear(&xml->Qry);

    if(MAJSTRGETLEN(xml->Formatstr))
       ajStrSetClear(&xml->Formatstr);

    if(MAJSTRGETLEN(xml->Filename))
       ajStrSetClear(&xml->Filename);

    ajStrDel(&xml->TextPtr);

    xml->Count = 0;
    xml->Fpos = 0L;
    xml->Format = 0;

    if(xml->Doc)
        ajDomDocumentDestroyNode(xml->Doc, &xml->Doc);

    return;
}
