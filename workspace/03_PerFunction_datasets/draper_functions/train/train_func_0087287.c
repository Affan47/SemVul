setComment(const char *name, const char *comment)
{
	if(name)
	{
		std::string myname=name;
		KeyValue *mydata = d_kv_map[myname];
		if(mydata)
		{
			mydata->setComment(comment);
		}
	}
}
