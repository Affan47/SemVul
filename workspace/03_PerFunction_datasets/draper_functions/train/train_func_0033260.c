createTFoot(  )
{
    if(!tFoot())
    {
        int exceptioncode = 0;
        ElementImpl* foot = new HTMLTableSectionElementImpl(docPtr(), ID_TFOOT, true );
        if(ElementImpl* firstBody = tFirstBody())
            insertBefore( foot, firstBody, exceptioncode );
        else
            appendChild(foot, exceptioncode);
    }
    return tFoot();
}
