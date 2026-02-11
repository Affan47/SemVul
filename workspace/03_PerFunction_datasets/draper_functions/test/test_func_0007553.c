setAttrUndefined(int attrName)
{
	attrValuev_type::iterator attr=attrValuev.find(attrName);
	if(attr==attrValuev.end()){

	}else{

		attrValuev.erase(attr);
	}
}
