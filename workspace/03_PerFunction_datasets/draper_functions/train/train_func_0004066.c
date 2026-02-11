getAttrValue(int attrName)
{
	attrValuev_type::iterator attr=attrValuev.find(attrName);
	if(attr==attrValuev.end()){

		return 0;
	}

	valuev_type valuev=attr->second;
	iom_value value=valuev.at(0);
	return value.getStr();
}
