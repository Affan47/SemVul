createDocumentType( const DOMString &qualifiedName, const DOMString &publicId,
                                                             const DOMString &systemId, int &exceptioncode )
{

    if (qualifiedName.isNull()) {
        exceptioncode = DOMException::NAMESPACE_ERR;
        return 0;
    }


    if (!Element::khtmlValidQualifiedName(qualifiedName)) {
        exceptioncode = DOMException::INVALID_CHARACTER_ERR;
        return 0;
    }


    if (!qualifiedName.isEmpty() && Element::khtmlMalformedQualifiedName(qualifiedName)) {
        exceptioncode = DOMException::NAMESPACE_ERR;
        return 0;
    }

    return new DocumentTypeImpl(this, 0, qualifiedName, publicId, systemId);
}
