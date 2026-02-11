registerXsd(QString name, int id, Node::VariantEncoder *enc) {
        registerDatatype(Uri(xsdPrefix.toString() + name), id, enc);
    }
