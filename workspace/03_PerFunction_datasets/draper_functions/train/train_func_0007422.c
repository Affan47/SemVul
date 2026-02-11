insertAttrObj(int attrName,int index,IomObject value)
{
	attrValuev_type::iterator attr=attrValuev.find(attrName);
	if(attr==attrValuev.end()){

		valuev_type valuev;
		valuev.push_back(iom_value(value));
		attrValuev[attrName]=valuev;
	}else{

		valuev_type valuev=attr->second;
		valuev.insert(valuev.begin()+index,iom_value(value));
		attrValuev[attrName]=valuev;
	}
}
