create(Parameter id)
{
	return boost::shared_ptr<ControlList>(new ControlList(id));
}
