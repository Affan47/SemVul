removeAttrObj(int attrName,int index)
{
	attrValuev_type::iterator attr=attrValuev.find(attrName);
	if(attr==attrValuev.end()){

	}else{

		valuev_type valuev=attr->second;
		valuev.erase(valuev.begin()+index);
		attrValuev[attrName]=valuev;
	}
}
