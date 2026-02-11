inheritedNotEqual( RenderStyle *other ) const
{
    return
	(
	    inherited_flags != other->inherited_flags ||
            inherited != other->inherited ||
            css3InheritedData != other->css3InheritedData ||
            m_svgStyle->inheritedNotEqual(other->m_svgStyle.get())
	    );
}
