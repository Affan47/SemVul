finish()
{
    if (m_executingScript) {

        m_explicitFinishParsingNeeded = true;
        return;
    }
    m_source.setFinished( true );
    if (!m_noErrors) {


        int exceptioncode = 0;
        while (m_doc->hasChildNodes())
            static_cast<NodeImpl*>(m_doc)->removeChild(m_doc->firstChild(),exceptioncode);

        QString line, errorLocPtr;
        if ( m_handler.errorLine != -1 ) {
            QString xmlCode = m_source.data();
            QTextStream stream(&xmlCode, QIODevice::ReadOnly);
            for (int lineno = 0; lineno < m_handler.errorLine-1; lineno++)
                stream.readLine();
            line = stream.readLine();

            for (long colno = 0; colno < m_handler.errorCol-1; colno++)
                errorLocPtr += ' ';
            errorLocPtr += '^';
        }


        DocumentImpl *doc = m_doc;
        NodeImpl *html = doc->createElementNS(XHTML_NAMESPACE,"html");
        NodeImpl   *body = doc->createElementNS(XHTML_NAMESPACE,"body");
        NodeImpl     *h1 = doc->createElementNS(XHTML_NAMESPACE,"h1");
        NodeImpl       *headingText = doc->createTextNode(i18n("XML parsing error"));
        NodeImpl     *errorText = doc->createTextNode(m_handler.errorProtocol());
        NodeImpl     *hr = 0;
        NodeImpl     *pre = 0;
        NodeImpl     *lineText = 0;
        NodeImpl     *errorLocText = 0;
        if ( !line.isNull() ) {
            hr = doc->createElementNS(XHTML_NAMESPACE,"hr");
            pre = doc->createElementNS(XHTML_NAMESPACE,"pre");
            lineText = doc->createTextNode(line+'\n');
            errorLocText = doc->createTextNode(errorLocPtr);
        }


        doc->appendChild(html,exceptioncode);
        html->appendChild(body,exceptioncode);
        body->appendChild(h1,exceptioncode);
        h1->appendChild(headingText,exceptioncode);
        body->appendChild(errorText,exceptioncode);
        body->appendChild(hr,exceptioncode);
        body->appendChild(pre,exceptioncode);
        if ( pre ) {
            pre->appendChild(lineText,exceptioncode);
            pre->appendChild(errorLocText,exceptioncode);
        }


        h1->close();
        if ( pre ) pre->close();
        body->close();

        m_doc->recalcStyle( NodeImpl::Inherit );
        m_doc->updateRendering();
    }
    else {


        m_doc->updateStyleSelector();
    }


    end();
}
