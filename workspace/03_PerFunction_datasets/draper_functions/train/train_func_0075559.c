AddAttr(vAttrPtr attr)
{


	if( !attr.Get() ) {

		return;
	}

	b_vformat_add_attribute(m_format, attr.Extract());
}
