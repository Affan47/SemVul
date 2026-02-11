hideTextAux(QDomElement & parent, bool hideChildren) {
    if (hideChildren || parent.tagName() == "text") {
        parent.setTagName("g");
        hideChildren = true;
    }

    QDomElement child = parent.firstChildElement();
    while (!child.isNull()) {
        hideTextAux(child, hideChildren);
        child = child.nextSiblingElement();
    }
}
