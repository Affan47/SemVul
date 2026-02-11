setNextMix(XERCES_CPP_NAMESPACE::DOMDocument* doc)
	{
		CAMsg::printMsg(LOG_DEBUG,"setNextMix() - start\n");
    DOMElement* elemRoot = doc->getDocumentElement();


    DOMElement* elemSig;
    getDOMChildByName(elemRoot, OPTIONS_NODE_SIGNATURE, elemSig, false);


    DOMElement* elemCert;
    getDOMChildByName(elemSig, OPTIONS_NODE_X509DATA, elemCert,true);
    if(elemSig!=NULL)
        m_pNextMixCertificate = CACertificate::decode(elemCert->getFirstChild(),CERT_X509CERTIFICATE);

    DOMElement* elemOptionsRoot = m_docMixXml->getDocumentElement();
    DOMElement* elemOptionsCerts;
    getDOMChildByName(elemOptionsRoot, OPTIONS_NODE_CERTIFICATE_LIST, elemOptionsCerts, false);
    DOMElement* elemOptionsNextMixCert;

    if(getDOMChildByName(elemOptionsRoot, OPTIONS_NODE_NEXT_MIX_CERTIFICATE, elemOptionsNextMixCert, false) != E_SUCCESS)
    {
        elemOptionsNextMixCert = createDOMElement(m_docMixXml, OPTIONS_NODE_NEXT_MIX_CERTIFICATE);
        elemOptionsCerts->appendChild(elemOptionsNextMixCert);
        elemOptionsNextMixCert->appendChild(m_docMixXml->importNode(elemCert->getFirstChild(),true));
    }
    else
    {
        if(elemOptionsNextMixCert->hasChildNodes())
        {
            elemOptionsNextMixCert->replaceChild(m_docMixXml->importNode(elemCert->getFirstChild(),true),
                    elemOptionsNextMixCert->getFirstChild());
        }
        else
        {
            elemOptionsNextMixCert->appendChild(m_docMixXml->importNode(elemCert->getFirstChild(),true));
        }
    }
		CAMsg::printMsg(LOG_DEBUG,"setNextMix() - certificates done\n");
    DOMElement* elemNextMix;
    getDOMChildByName(elemRoot, OPTIONS_NODE_LISTENER_INTERFACE, elemNextMix,true);

    DOMElement* elemOptionsNetwork;
    DOMElement* elemOptionsNextMixInterface;

    if(getDOMChildByName(elemOptionsRoot, OPTIONS_NODE_NETWORK, elemOptionsNetwork, false) != E_SUCCESS)
    {
        elemOptionsNetwork = createDOMElement(m_docMixXml, OPTIONS_NODE_NETWORK);
        elemOptionsRoot->appendChild(elemOptionsNetwork);
    }

    if(getDOMChildByName(elemOptionsNetwork, OPTIONS_NODE_NEXT_MIX, elemOptionsNextMixInterface, false) != E_SUCCESS)
    {
        elemOptionsNextMixInterface = createDOMElement(m_docMixXml, OPTIONS_NODE_NEXT_MIX);
        elemOptionsNetwork->appendChild(elemOptionsNextMixInterface);
    }
    else
    {
        while(elemOptionsNextMixInterface->hasChildNodes())
        {
            elemOptionsNextMixInterface->removeChild(elemOptionsNextMixInterface->getFirstChild());
        }
    }

    DOMNode* interfaceData = elemNextMix->getFirstChild();
    while(interfaceData != NULL)
    {
        elemOptionsNextMixInterface->appendChild(m_docMixXml->importNode(interfaceData,true));
        interfaceData = interfaceData->getNextSibling();
    }

		CAMsg::printMsg(LOG_DEBUG,"setNextMix() - end\n");
    return processXmlConfiguration(m_docMixXml);
}
