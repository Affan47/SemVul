setStyle(RenderStyle* _style)
{
    RenderObject::setStyle(_style);


    if (style()->isGenerated())
    {


        RenderStyle *pseudoStyle = new RenderStyle();
        pseudoStyle->inheritFrom(style());
        pseudoStyle->ref();
        RenderObject *child = firstChild();
        while (child != 0)
        {
            child->setStyle(pseudoStyle);
            child = child->nextSibling();
        }
        pseudoStyle->deref();
    }
}
