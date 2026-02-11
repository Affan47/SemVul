ownerSVGElement() const
{
    Node* n = isShadowNode() ? const_cast<SVGElement*>(this)->shadowParentNode() : parentNode();
    while (n) {
        if (n->id() == SVGNames::svgTag.id())
            return static_cast<SVGSVGElement*>(n);

        n = n->isShadowNode() ? n->shadowParentNode() : n->parentNode();
    }

    return 0;
}
