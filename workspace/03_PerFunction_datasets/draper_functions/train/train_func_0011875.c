invalidateResourcesInAncestorChain() const
{
    Node* node = parentNode();
    while (node) {
        if (!node->isSVGElement())
            break;

        SVGElement* element = static_cast<SVGElement*>(node);
        if (SVGStyledElement* styledElement = static_cast<SVGStyledElement*>(element->isStyled() ? element : 0)) {


        }

        node = node->parentNode();
    }
}
