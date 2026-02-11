updateInstance(SVGElement* element)
{
    ASSERT(element == m_element);
    ASSERT(m_shadowTreeElement);
    Q_UNUSED(element);


    if (m_element->hasTagName(SVGNames::symbolTag) ||
        m_element->hasTagName(SVGNames::svgTag) ||
        containsUseChildNode(m_element.get())) {
        m_useElement->buildPendingResource();
        return;
    }


    WTF::PassRefPtr<Node> clone = m_element->cloneNode(true);
    SVGUseElement::removeDisallowedElementsFromSubtree(clone.get());
    SVGElement* svgClone = 0;
    if (clone && clone->isSVGElement())
        svgClone = static_cast<SVGElement*>(clone.get());
    ASSERT(svgClone);


    int ec = 0;
    m_shadowTreeElement->parentNode()->replaceChild(clone.releaseRef(), m_shadowTreeElement, ec);
    ASSERT(ec == 0);

    m_shadowTreeElement = svgClone;
}
